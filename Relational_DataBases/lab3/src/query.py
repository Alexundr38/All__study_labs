from sqlalchemy import func, and_, desc, or_
from create import *
import pandas as pd
from tabulate import tabulate


def execute_query(db, query_number):
    if query_number == 1:
        out_data = select_vacancy_company(db)
    elif query_number == 2:
        out_data = select_vacancy_name(db)
    elif query_number == 3:
        out_data = select_count_vacancy(db)
    elif query_number == 4:
        out_data = select_archive_vacancy(db)
    elif query_number == 5:
        out_data = select_mean_salary(db)
    elif query_number == 6:
        out_data = select_worker_education(db)
    elif query_number == 7:
        out_data = select_worker_place(db)
    elif query_number == 8:
        out_data = select_vacancy_salary_experience(db)
    else:
        print("Wrong query number")
        return
    print(tabulate(out_data, headers='keys', tablefmt='plain', showindex=False, stralign='left', numalign='left'))

def select_all(db, table_name):
    name_to_table = {
        'passport': Passport,
        'tin': Tin,
        'workbook': Workbook,
        'worker': Worker,
        'worker_workbook': WorkerWorkbook,
        'education': Education,
        'worker_education': WorkerEducation,
        'post': Post,
        'resume': Resume,
        'skill': Skill,
        'resume_skill': ResumeSkill,
        'field_of_activity': FieldOfActivity,
        'employer': Employer,
        'presentation_file': PresentationFile,
        'workbook_writing': WorkbookWriting,
        'workbook_employer_writing': WorkbookEmployerWriting,
        'vacancy': Vacancy,
        'requirement': Requirement,
        'vacancy_requirement': VacancyRequirement,
        'condition': Condition,
        'vacancy_condition': VacancyCondition
    }

    try:
        model_class = name_to_table[table_name]

        query = db.query(
            model_class
        ).all()

        print(table_name)
        for row in query:
            print(row)
    except Exception as e:
        print(f'Table {table_name} does not exist')


# 1. Какие вакансии есть у данной компании?
def select_vacancy_company(db):
    query = db.query(
        Vacancy.name.label('vacancy_name'),
        Employer.name.label('company'),
        Post.name.label('post'),
        Vacancy.salary,
        Vacancy.address,
        Vacancy.experience,
        Vacancy.comment,
        Vacancy.status
    ).join(Employer)\
    .join(Post)\
    .filter(Employer.name == 'КиберПредсказания')\
    .all()

    out_data = pd.DataFrame([{
        'Компания': q.vacancy_name,
        'Название_вакансии': q.vacancy_name,
        'Должность': q.post,
        'Зарплата': q.salary,
        'Адрес': q.address,
        'Опыт': q.experience if q.experience else None,
        'Комментарий': q.comment if q.comment else None,
        'Статус': q.status
    } for q in query])

    return(out_data)


# 2. Какая вакансия подходит мне по названию?
def select_vacancy_name(db):
    query = db.query(
        Vacancy.name.label('vacancy_name'),
        Employer.name.label('company'),
        Post.name.label('post'),
        Vacancy.salary,
    ).join(Employer)\
    .join(Post)\
    .filter(Vacancy.name.like('%склад%'))\
    .all()

    out_data = pd.DataFrame([{
        'Название_вакансии': q.vacancy_name,
        'Компания': q.company,
        'Должность': q.post,
        'Зарплата': q.salary
    } for q in query])

    return(out_data)


# 3. Сколько поблизости вакансий от меня (указание улицы)?
def select_count_vacancy(db):
    query = db.query(
        func.count(Vacancy.name).label('vacancy_count')
    ).filter(Vacancy.address.like('%Варшавская%'))\
    .all()

    out_data = pd.DataFrame([{
        'Количество_вакансий': q.vacancy_count
    } for q in query])

    return(out_data)


# 4. Какие вакансии были помещены в архив у компании?
def select_archive_vacancy(db):
    query = db.query(
        Vacancy.name.label('vacancy_name'),
        Employer.name.label('company'),
        Post.name.label('post'),
        Vacancy.salary
    ).join(Employer)\
    .join(Post)\
    .filter(and_(
        Employer.name == 'ОАО "Везем"',
        Vacancy.status == VacancyStatus.archive
    ))\
    .all()

    out_data = pd.DataFrame([{
        'Название_вакансии': q.vacancy_name,
        'Компания': q.company,
        'Должность': q.post,
        'Зарплата': q.salary
    } for q in query])

    return(out_data)


# 5. Средняя ЗП каждого работодателя?
def select_mean_salary(db):
    query = db.query(
        Employer.name.label('company'),
        func.round(func.avg(Vacancy.salary), 2).label('mean_salary')
    ).join(Employer)\
    .group_by(Employer.name)\
    .order_by(desc('mean_salary'))\
    .all()

    out_data = pd.DataFrame([{
        'Компания': q.company,
        'Средняя_зп': q.mean_salary
    } for q in query])

    return(out_data)


#  6. Сколько работников ищут работу, имея высшее образование?
def select_worker_education(db):
    query = db.query(
        func.count(func.distinct(Resume.worker_id)).label('count_worker')
    ).join(Worker)\
    .join(WorkerEducation)\
    .join(Education)\
    .filter(Education.type == EducationType.higher)\
    .all()

    out_data = pd.DataFrame([{
        'Количество_работников': q.count_worker
    } for q in query])

    return(out_data)


# 7. Сколько работников имело более 3-х мест работы?
def select_worker_place(db):
    query = db.query(
        func.count(func.distinct(Worker.worker_id)).label('count_worker')
    ).join(WorkerWorkbook)\
    .join(Workbook)\
    .join(WorkbookEmployerWriting)\
    .join(WorkbookWriting)\
    .group_by(Worker.worker_id)\
    .having(func.count(func.distinct(WorkbookEmployerWriting.employer_id)) > 3)\
    .all()

    out_data = pd.DataFrame([{
        'Количество_работников': q.count_worker
    } for q in query])

    return(out_data)


# 8. Какие вакансии имеют ЗП более 100 000р и не требуют опыта работы?
def select_vacancy_salary_experience(db):
    query = db.query(
        Vacancy.name.label('vacancy_name'),
        Employer.name.label('company'),
        Post.name.label('post'),
        Vacancy.salary,
        Vacancy.experience
    ).join(Employer)\
    .join(Post)\
    .filter(and_(
        Vacancy.salary > 100000,
        or_(
            Vacancy.experience == 0,
            Vacancy.experience.is_(None)
        )
    ))\
    .all()

    out_data = pd.DataFrame([{
        'Название_вакансии': q.vacancy_name,
        'Компания': q.company,
        'Должность': q.post,
        'Зарплата': q.salary,
        'Опыт работы': q.experience
    } for q in query])

    return(out_data)