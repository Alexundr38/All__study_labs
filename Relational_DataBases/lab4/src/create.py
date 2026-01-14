from sqlalchemy.orm import DeclarativeBase, relationship
from sqlalchemy import UniqueConstraint, Numeric, Column, Integer, String, Date, ForeignKey, Enum, BigInteger
import enum

class Base(DeclarativeBase):
    pass

class EducationType(enum.Enum):
    higher = 'Высшее'
    secondary = 'Среднее'


class VacancyStatus(enum.Enum):
    active = 'Активна'
    archive = 'В архиве'
    deleted = 'Удалена'


class WritingType(enum.Enum):
    applying = 'Зачисление'
    dismissal = 'Увольнение'
    transition = 'Переход'
    change_position = 'Изменение должности'


class Passport(Base):
    __tablename__ = 'passport'

    passport_id = Column(Integer, primary_key=True, autoincrement=True)
    passport_number = Column(Integer, nullable=False)
    passport_series = Column(Integer, nullable=False)

    __table_args__ = (
        UniqueConstraint('passport_number', 'passport_series'),
    )

    worker = relationship('Worker', back_populates='passport', uselist=False)

    def __repr__(self):
        return f'Passport (id: {self.passport_id}, number: {self.passport_number}, series: {self.passport_series})'


class Tin(Base):
    __tablename__ = 'tin'

    tin_id = Column(Integer, primary_key=True, autoincrement=True)
    tin = Column(BigInteger, unique=True, nullable=False)

    worker = relationship('Worker', back_populates='tin', uselist=False)

    def __repr__(self):
        return f'TIN (id: {self.tin_id}, number: {self.tin})'


class Workbook(Base):
    __tablename__ = 'workbook'

    workbook_id = Column(Integer, primary_key=True, autoincrement=True)
    workbook_number = Column(Integer, unique=True, nullable=False)
    issue_date = Column(Date, nullable=False)

    worker = relationship('WorkerWorkbook',  back_populates='workbook')
    workbook_writings = relationship('WorkbookEmployerWriting', back_populates='workbook')

    def __repr__(self):
        return f'Workbook (id: {self.workbook.id}, number: {self.workbook_number}, issue_date: {self.issue_date})'


class Worker(Base):
    __tablename__ = 'worker'

    worker_id = Column(Integer, primary_key=True, autoincrement=True)
    passport_id = Column(Integer, ForeignKey('passport.passport_id'), nullable=False)
    tin_id = Column(Integer, ForeignKey('tin.tin_id'), nullable=False)
    birthday = Column(Date)

    passport = relationship('Passport', back_populates='worker')
    tin = relationship('Tin', back_populates='worker')
    workbooks = relationship('WorkerWorkbook', back_populates='worker')
    educations = relationship('WorkerEducation', back_populates='worker')
    resumes = relationship('Resume', back_populates='worker')

    def __repr__(self):
        return f'Worker (id: {self.worker_id}, tin_id: {self.tin_id}, passport_id: {self.passport.passport_id})'


class WorkerWorkbook(Base):
    __tablename__ = 'worker_workbook'

    worker_id = Column(Integer, ForeignKey('worker.worker_id'), primary_key=True)
    workbook_id = Column(Integer, ForeignKey('workbook.workbook_id'), primary_key=True)

    workbook = relationship('Workbook', back_populates='worker')
    worker = relationship('Worker', back_populates='workbooks')

    def __repr__(self):
        return f'WorkerWorkbook (worker_id: {self.worker_id}, workbook_id: {self.workbook_id})'


class Education(Base):
    __tablename__ = 'education'

    education_id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(255), nullable=False)
    type = Column(Enum(EducationType), nullable=False)

    workers = relationship('WorkerEducation', back_populates='education')

    def __repr__(self):
        return f'Education (id: {self.education_id}, name: {self.name}, type: {self.type})'


class WorkerEducation(Base):
    __tablename__ = 'worker_education'

    worker_id = Column(Integer, ForeignKey('worker.worker_id'), primary_key=True)
    education_id = Column(Integer, ForeignKey('education.education_id'), primary_key=True)
    enroll_date = Column(Date, nullable=False)

    worker = relationship('Worker', back_populates='educations')
    education = relationship('Education', back_populates='workers')

    def __repr__(self):
        return f'WorkerEducation (worker_id: {self.worker_id}, education_id: {self.education_id}, enroll_date: {self.enroll_date})'


class Post(Base):
    __tablename__ = 'post'

    post_id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(255), unique=True, nullable=False)

    vacancies = relationship('Vacancy', back_populates='post')
    resumes = relationship('Resume', back_populates='post')

    def __repr__(self):
        return f'Post (id: {self.post_id}, name: {self.name})'


class Resume(Base):
    __tablename__ = 'resume'

    resume_id = Column(Integer, primary_key=True, autoincrement=True)
    worker_id = Column(Integer, ForeignKey('worker.worker_id'), nullable=False)
    post_id = Column(Integer, ForeignKey('post.post_id'), nullable=False)
    salary = Column(Numeric(8,2), nullable=False)

    worker = relationship('Worker', back_populates='resumes')
    post = relationship('Post', back_populates='resumes')
    skills = relationship('ResumeSkill', back_populates='resumes')

    def __repr__(self):
        return f'Resume (id: {self.resume_id}, worker_id: {self.worker_id}, post_id: {self.post_id}, salary: {self.salary})'


class Skill(Base):
    __tablename__ = 'skill'

    skill_id = Column(Integer, primary_key=True, autoincrement=True)
    description = Column(String(255), unique=True, nullable=False)

    resumes = relationship('ResumeSkill', back_populates='skills')

    def __repr__(self):
        return f'Skill (id: {self.skill_id}, descriprion: {self.description})'


class ResumeSkill(Base):
    __tablename__ = 'resume_skill'

    resume_id = Column(Integer, ForeignKey('resume.resume_id'), primary_key=True)
    skill_id = Column(Integer, ForeignKey('skill.skill_id'), primary_key=True)

    resumes = relationship('Resume', back_populates='skills')
    skills = relationship('Skill', back_populates='resumes')

    def __repr__(self):
        return f'ResumeSkill (resume_id: {self.resume_id}, skill_id: {self.skill_id})'


class FieldOfActivity(Base):
    __tablename__ = 'field_of_activity'

    activity_id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(255), unique=True, nullable=False)

    employers = relationship('Employer', back_populates='field_of_activity')

    def __repr__(self):
        return f'FieldOfActivity (id: {self.activity_id}, name: {self.name})'


class Employer(Base):
    __tablename__ = 'employer'

    employer_id = Column(Integer, primary_key=True, autoincrement=True)
    activity_id = Column(Integer, ForeignKey('field_of_activity.activity_id'), nullable=False)
    name = Column(String(255), nullable=False)
    photo_url = Column(String(255))
    description = Column(String(255))

    field_of_activity = relationship('FieldOfActivity', back_populates='employers')
    presentation_files = relationship('PresentationFile', back_populates='employer')
    vacancies = relationship('Vacancy', back_populates='employer')
    workbook_writings = relationship('WorkbookEmployerWriting', back_populates='employer')

    def __repr__(self):
        return f'Employer (id: {self.employer_id}, activity_id: {self.activity_id}, name: {self.name}), name: {self.name}, photo_url: {self.photo_url}, description: {self.description})'


class PresentationFile(Base):
    __tablename__ = 'presentation_file'

    file_id = Column(Integer, primary_key=True, autoincrement=True)
    employer_id = Column(Integer, ForeignKey('employer.employer_id'), nullable=False)
    name = Column(String(255), nullable=False)
    url = Column(String(255), nullable=False)

    employer = relationship('Employer', back_populates='presentation_files')

    def __repr__(self):
        return f'PresentationFile (id: {self.file_id}, employer_id: {self.employer_id}, name: {self.name}, url: {self.url})'


class WorkbookWriting(Base):
    __tablename__ = 'workbook_writing'

    writing_id = Column(Integer, primary_key=True, autoincrement=True)
    type = Column(Enum(WritingType), nullable=False)
    date = Column(Date, nullable=False)
    description = Column(String(255))

    workbook_writings = relationship('WorkbookEmployerWriting', back_populates='workbook_writings')

    def __repr__(self):
        return f'WorkbookWriting (id: {self.writing_id}, type: {self.type}, date: {self.date}, description: {self.description})'


class WorkbookEmployerWriting(Base):
    __tablename__ = 'workbook_employer_writing'

    writing_id = Column(Integer, ForeignKey('workbook_writing.writing_id'), primary_key=True)
    workbook_id = Column(Integer, ForeignKey('workbook.workbook_id'), primary_key=True)
    employer_id = Column(Integer, ForeignKey('employer.employer_id'), primary_key=True)

    workbook_writings = relationship('WorkbookWriting', back_populates='workbook_writings')
    employer = relationship('Employer', back_populates='workbook_writings')
    workbook = relationship('Workbook', back_populates='workbook_writings')

    def __repr__(self):
        return f'WorkbookEmployerWriting (writing_id: {self.writing_id}, workbook_id: {self.workbook_id}, employer_id: {self.employer_id})'


class Vacancy(Base):
    __tablename__ = 'vacancy'

    vacancy_id = Column(Integer, primary_key=True, autoincrement=True)
    post_id = Column(Integer, ForeignKey('post.post_id'), nullable=False)
    employer_id = Column(Integer, ForeignKey('employer.employer_id'), nullable=False)
    name = Column(String(255), nullable=False)
    address = Column(String(255), nullable=False)
    salary = Column(Numeric(8,2), nullable=False)
    experience = Column(Integer)
    comment = Column(String(255))
    status = Column(Enum(VacancyStatus), nullable=False)

    post = relationship('Post', back_populates='vacancies')
    employer = relationship('Employer', back_populates='vacancies')
    requirements = relationship('VacancyRequirement', back_populates='vacancies')
    conditions = relationship('VacancyCondition', back_populates='vacancies')

    def __repr__(self):
        return f'Vacancy (id: {self.vacancy_id}, post_id: {self.post_id}, employer_id: {self.employer_id}, name: {self.name}, address: {self.address}, salary: {self.salary}, experience: {self.experience}, comment: {self.comment}, status: {self.status})'


class Requirement(Base):
    __tablename__ = 'requirement'

    requirement_id = Column(Integer, primary_key=True, autoincrement=True)
    description = Column(String(255), unique=True, nullable=False)

    vacancies = relationship('VacancyRequirement', back_populates='requirements')

    def __repr__(self):
        return f'Requirement (id: {self.requirement_id}, description: {self.description})'


class VacancyRequirement(Base):
    __tablename__ = 'vacancy_requirement'

    vacancy_id = Column(Integer, ForeignKey('vacancy.vacancy_id'), primary_key=True)
    requirement_id = Column(Integer, ForeignKey('requirement.requirement_id'), primary_key=True)

    vacancies = relationship('Vacancy', back_populates='requirements')
    requirements = relationship('Requirement', back_populates='vacancies')

    def __repr__(self):
        return f'VacancyRequirement (vacancy_id: {self.vacancy_id}, requirement: {self.requirement})'


class Condition(Base):
    __tablename__ = 'condition'

    condition_id = Column(Integer, primary_key=True, autoincrement=True)
    description = Column(String(255), unique=True, nullable=False)

    vacancies = relationship('VacancyCondition', back_populates='conditions')

    def __repr__(self):
        return f'Condition (id: {self.condition_id}, description: {self.description})'


class VacancyCondition(Base):
    __tablename__ = 'vacancy_condition'

    vacancy_id = Column(Integer, ForeignKey('vacancy.vacancy_id'), primary_key=True)
    condition_id = Column(Integer, ForeignKey('condition.condition_id'), primary_key=True)

    vacancies = relationship('Vacancy', back_populates='conditions')
    conditions = relationship('Condition', back_populates='vacancies')

    def __repr__(self):
        return f'VacancyCondition (vacancy_id: {self.vacancy_id}, condition: {self.condition_id})'



