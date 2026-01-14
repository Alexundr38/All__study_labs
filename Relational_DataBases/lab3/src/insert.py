from create import *
from datetime import date

passports = [
    Passport(passport_number=3317, passport_series=627219),
    Passport(passport_number=3214, passport_series=745323),
    Passport(passport_number=3421, passport_series=231421),
    Passport(passport_number=3142, passport_series=892156),
    Passport(passport_number=3345, passport_series=324561),
    Passport(passport_number=3214, passport_series=234741)
]

tins = [
    Tin(tin=505021345692),
    Tin(tin=432102345672),
    Tin(tin=476221556514),
    Tin(tin=813267892103),
    Tin(tin=456969651393),
    Tin(tin=158923546790)
]

workers = [
    Worker(passport_id=2, tin_id=3, birthday=date(1992, 2, 14)),
    Worker(passport_id=1, tin_id=4, birthday=date(1996, 4, 19)),
    Worker(passport_id=5, tin_id=6, birthday=date(1982, 10, 1)),
    Worker(passport_id=6, tin_id=1, birthday=date(2003, 1, 27)),
    Worker(passport_id=3, tin_id=5, birthday=date(1979, 7, 8)),
    Worker(passport_id=4, tin_id=2, birthday=date(2000, 1, 1))
]

educations = [
    Education(name='СПБГЭТУ',   type=EducationType.higher),
    Education(name='МАИ',       type=EducationType.higher),
    Education(name='КЛПК',      type=EducationType.secondary),
    Education(name='ВятГУ',     type=EducationType.higher),
    Education(name='ИТМО',      type=EducationType.higher),
    Education(name='РГГУ',      type=EducationType.secondary),
    Education(name='КПиАС',     type=EducationType.secondary),
    Education(name='СПБГУГА',   type=EducationType.higher)
]

worker_educations = [
    WorkerEducation(worker_id=1, education_id=3, enroll_date=date(2010, 9, 1)),
    WorkerEducation(worker_id=1, education_id=1, enroll_date=date(2015, 8, 25)),
    WorkerEducation(worker_id=3, education_id=4, enroll_date=date(2012, 7, 29)),
    WorkerEducation(worker_id=5, education_id=8, enroll_date=date(2000, 8, 27)),
    WorkerEducation(worker_id=5, education_id=5, enroll_date=date(1992, 8, 28)),
    WorkerEducation(worker_id=4, education_id=2, enroll_date=date(2019, 9, 1)),
    WorkerEducation(worker_id=6, education_id=1, enroll_date=date(2018, 8, 23))
]

workbooks = [
    Workbook(workbook_number=8627821, issue_date=date(2006, 12, 14)),
    Workbook(workbook_number=5423109, issue_date=date(2001, 3, 27)),
    Workbook(workbook_number=1234901, issue_date=date(1997, 9, 2)),
    Workbook(workbook_number=4298134, issue_date=date(2015, 2, 13)),
    Workbook(workbook_number=9823518, issue_date=date(2020, 7, 9)),
    Workbook(workbook_number=7349821, issue_date=date(2025, 1, 1)),
    Workbook(workbook_number=2354890, issue_date=date(2017, 9, 18))
]

worker_workbooks = [
    WorkerWorkbook(worker_id=1, workbook_id=1),
    WorkerWorkbook(worker_id=3, workbook_id=2),
    WorkerWorkbook(worker_id=6, workbook_id=5),
    WorkerWorkbook(worker_id=5, workbook_id=3),
    WorkerWorkbook(worker_id=4, workbook_id=6),
    WorkerWorkbook(worker_id=5, workbook_id=4),
    WorkerWorkbook(worker_id=2, workbook_id=7)
]

posts = [
    Post(name='Программист на python'),
    Post(name='Курьер'),
    Post(name='Складовщик'),
    Post(name='HR-менеджер'),
    Post(name='Кассир'),
    Post(name='Водитель автобуса'),
    Post(name='Маркетолог'),
    Post(name='Data-Scientist'),
    Post(name='Парикмахер'),
    Post(name='Разнорабочий')
]

skills = [
    Skill(description='Умение работать в команде'),
    Skill(description='Водительская категория D'),
    Skill(description='Программирование на python'),
    Skill(description='Мат. статистика'),
    Skill(description='Трудолюбие'),
    Skill(description='Терпеливость'),
    Skill(description='Быстрая адаптация к изменениям'),
    Skill(description='Умение работать в стрессовой обстановке'),
    Skill(description='Спортивное физическое телосложение')
]

resumes = [
    Resume(worker_id=1, post_id=4,  salary=75000),
    Resume(worker_id=5, post_id=6,  salary=57500.50),
    Resume(worker_id=3, post_id=3,  salary=70000),
    Resume(worker_id=3, post_id=10, salary=47000.99),
    Resume(worker_id=4, post_id=8,  salary=250000),
    Resume(worker_id=6, post_id=1,  salary=150000),
    Resume(worker_id=5, post_id=2,  salary=180000)
]

resume_skills = [
    ResumeSkill(resume_id=1, skill_id=7),
    ResumeSkill(resume_id=1, skill_id=8),
    ResumeSkill(resume_id=1, skill_id=1),
    ResumeSkill(resume_id=5, skill_id=4),
    ResumeSkill(resume_id=6, skill_id=3),
    ResumeSkill(resume_id=7, skill_id=5),
    ResumeSkill(resume_id=7, skill_id=7),
    ResumeSkill(resume_id=2, skill_id=2),
    ResumeSkill(resume_id=3, skill_id=9),
    ResumeSkill(resume_id=3, skill_id=5)
]

field_of_activitys = [
    FieldOfActivity(name='Перевозка пассажиров'),
    FieldOfActivity(name='IT'),
    FieldOfActivity(name='Доставка'),
    FieldOfActivity(name='Продажи'),
    FieldOfActivity(name='Производство продукции'),
]

employers = [
    Employer(activity_id=2, name='КиберПредсказания',   photo_url='https://photo1',
             description='Компания, занимающаяся аналитикой данных, от сторонних организаций'),
    Employer(activity_id=3, name='ЯнлексПитье',         photo_url='https://photo2',
             description='Служба доставки питья на дом'),
    Employer(activity_id=1, name='ОАО "Везем"',         photo_url='https://photo3',
             description='Организация, осуществляющая перевозку пассажиров по маршрутам дальнего следования'),
    Employer(activity_id=5, name='SuperFlowers',        photo_url='https://photo4',
             description='Производство блоков питания'),
    Employer(activity_id=4, name='ООО "Купи Слона"',    photo_url='https://photo5',
             description='Зоомагазин'),
    Employer(activity_id=5, name='ОкноДом',             photo_url='https://photo6',
             description='Отечественный производитель стеклопакетов')
]

presentation_files = [
    PresentationFile(employer_id=1, name='Презентация 1', url='https://file1'),
    PresentationFile(employer_id=1, name='Презентация 2', url='https://file2'),
    PresentationFile(employer_id=2, name='Презентация 1', url='https://file3'),
    PresentationFile(employer_id=5, name='Презентация 1', url='https://file4'),
    PresentationFile(employer_id=4, name='Презентация 1', url='https://file5')
]

requirements = [
    Requirement(description='Стрессоустойчивость'),
    Requirement(description='Знание ПДД'),
    Requirement(description='Знание python на базовом уровне'),
    Requirement(description='Знание python на повышенном уровне'),
    Requirement(description='Знание мат. статистики'),
    Requirement(description='Работа в команде'),
    Requirement(description='Хорошо поставленная речь'),
    Requirement(description='Наличие автомобиля'),
    Requirement(description='Работа из офиса'),
    Requirement(description='Работа из дома')
]

conditions = [
    Condition(description='Обустроенное рабочее место'),
    Condition(description='Предоставление ноутбука'),
    Condition(description='ДМС'),
    Condition(description='Гибкий рабочий график'),
    Condition(description='График работы 2 на 2'),
    Condition(description='Работа в большой компании'),
    Condition(description='Официальное трудоустройство'),
    Condition(description='Рабочий автомобиль от компании')
]

vacancies = [
    Vacancy(post_id=8, employer_id=1, name='DataScientist для Предсказаний',
            address='Варшавская улица, 63к1, Санкт-Петербург',  salary=180000.50,   experience=5,
            comment='Требуется DataScientist для предсказаний кибер будущего',      status=VacancyStatus.active),
    Vacancy(post_id=6, employer_id=3, name='Водитель рейсового автобуса',
            address='улица Костюшко, 17, Санкт-Петербург',      salary=83250,       experience=3,
            status=VacancyStatus.archive),
    Vacancy(post_id=4, employer_id=1, name='Менеджер по отбору кадров (HR)',
            address='Варшавская улица, 44, Санкт-Петербург',    salary=91000,       experience=7,
            comment='Нужен менеджер для подбора персонала в новую команду',         status=VacancyStatus.active),
    Vacancy(post_id=2, employer_id=2, name='Курьер доставки питья',
            address='Варшавская улица, 124, Санкт-Петербург',   salary=110000,
            status=VacancyStatus.active),
    Vacancy(post_id=3, employer_id=6, name='Начальник склада',
            address='Софийская улица, 8к5с4, Санкт-Петербург',  salary=87000,       experience=5,
            comment='Начальник-заведующий складом, управляет приемом и отправкой товара', status=VacancyStatus.archive),
    Vacancy(post_id=3, employer_id=6, name='Складовщик на новый склад',
            address='Софийская улица, 8к5с4, Санкт-Петербург',  salary=63000,
            status=VacancyStatus.active),
    Vacancy(post_id=7, employer_id=5, name='Маркетолог бренда',
            address='Московский проспект, 9, Санкт-Петербург',  salary=69000.99,
            comment='Ждем креативных людей для продвижения бренда!',                status=VacancyStatus.active)
]

vacancy_requirements = [
    VacancyRequirement(vacancy_id=1, requirement_id=3),
    VacancyRequirement(vacancy_id=1, requirement_id=4),
    VacancyRequirement(vacancy_id=3, requirement_id=6),
    VacancyRequirement(vacancy_id=3, requirement_id=7),
    VacancyRequirement(vacancy_id=7, requirement_id=9),
    VacancyRequirement(vacancy_id=4, requirement_id=8),
    VacancyRequirement(vacancy_id=5, requirement_id=1),
    VacancyRequirement(vacancy_id=5, requirement_id=7),
    VacancyRequirement(vacancy_id=2, requirement_id=2),
    VacancyRequirement(vacancy_id=1, requirement_id=10)
]

vacancy_conditions = [
    VacancyCondition(vacancy_id=1, condition_id=2),
    VacancyCondition(vacancy_id=1, condition_id=4),
    VacancyCondition(vacancy_id=2, condition_id=5),
    VacancyCondition(vacancy_id=2, condition_id=8),
    VacancyCondition(vacancy_id=6, condition_id=3),
    VacancyCondition(vacancy_id=7, condition_id=6),
    VacancyCondition(vacancy_id=4, condition_id=7),
    VacancyCondition(vacancy_id=5, condition_id=1)
]

workbook_writings = [
    WorkbookWriting(type=WritingType.applying,          date=date(2010, 1, 1)),
    WorkbookWriting(type=WritingType.change_position,   date=date(2018, 2, 13), description='Повышение должности'),
    WorkbookWriting(type=WritingType.applying,          date=date(1995, 7, 1)),
    WorkbookWriting(type=WritingType.dismissal,         date=date(1995, 11, 18)),
    WorkbookWriting(type=WritingType.applying,          date=date(1995, 12, 1)),
    WorkbookWriting(type=WritingType.dismissal,         date=date(1997, 5, 10)),
    WorkbookWriting(type=WritingType.applying,          date=date(1998, 1, 13)),
    WorkbookWriting(type=WritingType.dismissal,         date=date(2003, 3, 8)),
    WorkbookWriting(type=WritingType.applying,          date=date(2004, 5, 21)),
    WorkbookWriting(type=WritingType.applying,          date=date(2023, 7, 18))
]

workbook_employer_writings = [
    WorkbookEmployerWriting(writing_id=1,   workbook_id=1, employer_id=6),
    WorkbookEmployerWriting(writing_id=2,   workbook_id=1, employer_id=6),
    WorkbookEmployerWriting(writing_id=4,   workbook_id=4, employer_id=2),
    WorkbookEmployerWriting(writing_id=3,   workbook_id=4, employer_id=2),
    WorkbookEmployerWriting(writing_id=10,  workbook_id=6, employer_id=5),
    WorkbookEmployerWriting(writing_id=5,   workbook_id=4, employer_id=4),
    WorkbookEmployerWriting(writing_id=6,   workbook_id=4, employer_id=4),
    WorkbookEmployerWriting(writing_id=8,   workbook_id=3, employer_id=3),
    WorkbookEmployerWriting(writing_id=7,   workbook_id=3, employer_id=3),
    WorkbookEmployerWriting(writing_id=9,   workbook_id=3, employer_id=1),
]

def fill_database(db):
    db.add_all(passports)
    db.add_all(tins)
    db.add_all(workers)
    db.commit()

    db.add_all(educations)
    db.add_all(worker_educations)
    db.commit()

    db.add_all(posts)
    db.commit()

    db.add_all(skills)
    db.add_all(resumes)
    db.add_all(resume_skills)
    db.commit()

    db.add_all(field_of_activitys)
    db.add_all(employers)
    db.add_all(presentation_files)
    db.commit()

    db.add_all(workbooks)
    db.add_all(worker_workbooks)
    db.commit()

    db.add_all(workbook_writings)
    db.add_all(workbook_employer_writings)
    db.commit()

    db.add_all(vacancies)
    db.commit()

    db.add_all(requirements)
    db.add_all(vacancy_requirements)
    db.commit()

    db.add_all(conditions)
    db.add_all(vacancy_conditions)
    db.commit()