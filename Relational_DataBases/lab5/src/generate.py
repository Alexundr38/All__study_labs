from faker import Faker
from datetime import datetime, timedelta
import random
from create import *
from providers import *

fake = Faker('ru_RU')
fake.add_provider(SkillRequirementProvider)
fake.add_provider(EducationNameProvider)
fake.add_provider(FieldOfActivityProvider)
fake.add_provider(ConditionProvider)
fake.add_provider(PostProvider)

def generate_passports(count):
    passports = []
    passport_numbers = set()
    for i in range(count):
        while True:
            passport_number = [
                fake.random_int(min=1000, max=9999),
                fake.random_int(min=100000, max=999999)
            ]
            str_passport = str(passport_number[0]) + str(passport_number[1])
            if str_passport not in passport_numbers:
                passport_numbers.add(str_passport)

                passports.append(Passport(
                    passport_number=passport_number[0],
                    passport_series=passport_number[1]
                ))
                break
    return passports


def generate_tins(count):
    tins = []
    tin_numbers = set()
    for i in range(count):
        while True:
            tin = fake.random_int(min=100000000000, max=999999999999)
            if tin not in tin_numbers:
                tin_numbers.add(tin)

                tins.append(Tin(
                    tin=tin
                ))
                break
    return tins


def generate_workbooks(count):
    workbooks = []
    workbook_numbers = set()
    for i in range(count):
        while True:
            workbook_number = fake.random_int(min=1000000, max=9999999)
            if workbook_number not in workbook_numbers:
                workbook_numbers.add(workbook_number)

                workbooks.append(Workbook(
                    workbook_number=workbook_number,
                    issue_date=fake.date_between(start_date='-30y', end_date='today')
                ))
                break
    return workbooks

def generate_workers(count, passports, tins):
    workers = []
    for i in range(count):
        worker = Worker(
            passport_id = passports[i].passport_id,
            tin_id = tins[i].tin_id,
            birthday = fake.date_of_birth(minimum_age=18, maximum_age=80)
        )
        workers.append(worker)
    return workers


def generate_worker_workbooks(count, workers, workbooks):
    worker_workbooks = []
    for i in range(count):

        worker_workbooks.append(WorkerWorkbook(
            worker_id = workers[i].worker_id,
            workbook_id = workbooks[i].workbook_id
        ))
    return worker_workbooks


def generate_educations(count):
    educations = []
    names = set()
    for i in range(count):
        while True:
            name = fake.education_name()
            if name not in names:
                names.add(name)
                if "Колледж" in name:
                    type = EducationType.secondary
                else:
                    type = EducationType.higher

                educations.append(Education(
                    name = name,
                    type = type
                ))
                break
    return educations


def generate_worker_educations(workers, educations):
    worker_educations = []
    for worker in workers:
        count_educations = random.randint(0, 3)
        selected_educations = random.sample(educations, count_educations)

        for education in selected_educations:
            enroll_date = fake.date_between(
                start_date = worker.birthday + timedelta(days=365*14),
                end_date = 'today'
            )

            worker_educations.append(WorkerEducation(
                worker_id = worker.worker_id,
                education_id = education.education_id,
                enroll_date = enroll_date
            ))
    return worker_educations


def generate_posts(count=100):
    new_posts = []
    names = set()
    for i in range(count):
        while True:
            name = fake.post_name()
            if name not in names:
                names.add(name)

                new_posts.append(Post(
                    name=name
                ))
                break
    return new_posts


def generate_resumes(workers, posts):
    resumes = []
    for worker in workers:
        count_resumes = random.randint(0, 3)
        for i in range(count_resumes):

            resumes.append(Resume(
                worker_id = worker.worker_id,
                post_id = fake.random_element(posts).post_id,
                salary = fake.pyfloat(
                    left_digits=6,
                    right_digits=2,
                    min_value=40000,
                    positive=True
                )
            ))
    return resumes


def generate_skills(count):
    skills = []
    descriptions = set()
    for i in range(count):
        while True:
            description = fake.skill_requirement_description()
            if description not in descriptions:
                descriptions.add(description)

                skills.append(Skill(
                    description = description
                ))
                break
    return skills


def generate_resume_skills(resumes, skills):
    resume_skills = []
    for resume in resumes:

        count_skills = random.randint(0, 3)
        selected_skills = random.sample(skills, count_skills)
        for skill in selected_skills:

            resume_skills.append(ResumeSkill(
                resume_id = resume.resume_id,
                skill_id = skill.skill_id
            ))
    return resume_skills


def generate_field_of_activities(count):
    field_of_activities = []
    names = set()
    for i in range(count):
        while True:
            name = fake.field_of_activity()
            if name not in names:
                names.add(name)

                field_of_activities.append(FieldOfActivity(
                    name = name
                ))
                break
    return field_of_activities


def generate_employers(count, field_of_activities):
    employers = []
    for i in range(count):
        employers.append(Employer(
            name = fake.company(),
            activity_id = fake.random_element(field_of_activities).activity_id,
            photo_url = fake.image_url(),
            description = fake.text(max_nb_chars=200)
        ))
    return employers


def generate_presentation_file(count, employers):
    presentation_files = []
    for i in range(count):
        presentation_files.append(PresentationFile(
            name = f"Презентация {i}",
            url = fake.url(),
            employer_id = fake.random_element(employers).employer_id
        ))
    return presentation_files


def generate_workbook_writings(count):
    workbook_writings = []
    for i in range(count):
        workbook_writings.append(WorkbookWriting(
            type = fake.random_element(list(WritingType)),
            date = fake.date_between(start_date='-30y', end_date='today'),
            description = 'Молодец' if random.random () > 0.9 else None
        ))
    return workbook_writings


def generate_workbook_employer_writings(workbook_writings, workbooks, employers):
    workbook_employer_writings = []
    for writing in workbook_writings:
        workbook_employer_writings.append(WorkbookEmployerWriting(
            writing_id = writing.writing_id,
            workbook_id = fake.random_element(workbooks).workbook_id,
            employer_id = fake.random_element(employers).employer_id,
        ))
    return workbook_employer_writings


def generate_vacancies(count, posts, employers):
    vacancies = []
    for i in range(count):
        vacancies.append(Vacancy(
            post_id = fake.random_element(posts).post_id,
            employer_id = fake.random_element(employers).employer_id,
            name = fake.job(),
            address = fake.address(),
            salary = fake.pyfloat(
                left_digits=6,
                right_digits=2,
                min_value=40000,
                positive=True
            ),
            experience = random.randint(0, 10) if random.random () > 0.5 else None,
            comment = fake.text(max_nb_chars=200) if random.random () > 0.5 else None,
            status = fake.random_element(list(VacancyStatus))
        ))
    return vacancies


def generate_requirements(count):
    requirements = []
    descriptions = set()
    for i in range(count):
        while True:
            description = fake.skill_requirement_description()
            if description not in descriptions:
                descriptions.add(description)

                requirements.append(Requirement(
                    description = description
                ))
                break
    return requirements


def generate_vacancy_requirements(requirements, vacancies):
    vacancy_requirements = []
    for vacancy in vacancies:
        count_requirements = random.randint(0, 3)
        selected_requirements = random.sample(requirements, count_requirements)

        for requirement in selected_requirements:
            vacancy_requirements.append(VacancyRequirement(
                vacancy_id = vacancy.vacancy_id,
                requirement_id = requirement.requirement_id
            ))
    return vacancy_requirements


def generate_conditions(count):
    conditions = []
    descriptions = set()
    for i in range(count):
        while True:
            description = fake.condition_description()
            if description not in descriptions:
                descriptions.add(description)

                conditions.append(Condition(
                    description = description
                ))
                break
    return conditions


def generate_vacancy_conditions(conditions, vacancies):
    vacancy_conditions = []
    for vacancy in vacancies:
        count_conditions = random.randint(0, 3)
        selected_conditions = random.sample(conditions, count_conditions)
        for condition in selected_conditions:
            vacancy_conditions.append(VacancyCondition(
                vacancy_id = vacancy.vacancy_id,
                condition_id = condition.condition_id
            ))
    return vacancy_conditions