from flask import Flask, request, jsonify
from sqlalchemy import create_engine, func, and_, desc, or_, text
from sqlalchemy.orm import sessionmaker
from flask.json.provider import DefaultJSONProvider
from create import *
import json
from main import DATABASE_URL
from decimal import Decimal
from datetime import date, datetime

class RussianJSONProvider(DefaultJSONProvider):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.ensure_ascii = False

    def dumps(self, obj, **kwargs):
        kwargs.setdefault('ensure_ascii', False)
        return json.dumps(obj, **kwargs, cls=CustomJSONEncoder)


class CustomJSONEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Decimal):
            return float(obj)
        elif isinstance(obj, (date, datetime)):
            return obj.isoformat()
        return super().default(obj)


app = Flask(__name__)
app.json = RussianJSONProvider(app)
app.config['JSON_AS_ASCII'] = False

engine = create_engine(DATABASE_URL)
local_session = sessionmaker(bind=engine)


@app.route('/api/get-vacancy-company', methods=['GET'])
def get_vacancy_company():
    company_name = request.args.get('company-name', type=str, default='ЗАО «Одинцов Сидоров»')
    with local_session() as db:
        result = db.query(
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
        .filter(Employer.name == company_name) \
        .order_by('company')\
        .all()

        return jsonify([{
            'Компания': r.company,
            'Название_вакансии': r.vacancy_name,
            'Должность': r.post,
            'Зарплата': r.salary,
            'Адрес': r.address,
            'Опыт': r.experience if r.experience else None,
            'Комментарий': r.comment if r.comment else None,
            'Статус': r.status.value
        } for r in result])


@app.route('/api/get-vacancy-name', methods=['GET'])
def get_vacancy_name():
    vacancy_name = request.args.get('vacancy-name', type=str, default='Художник')
    with local_session() as db:
        result = db.query(
            Vacancy.name.label('vacancy_name'),
            Employer.name.label('company'),
            Post.name.label('post'),
            Vacancy.salary,
        ).join(Employer) \
        .join(Post) \
        .filter(Vacancy.name.like(f'%{vacancy_name}%')) \
        .order_by('company') \
        .all()

        return jsonify([{
            'Название_вакансии': r.vacancy_name,
            'Компания': r.company,
            'Должность': r.post,
            'Зарплата': r.salary
        } for r in result])



@app.route('/api/get-count-vacancy-street', methods=['GET'])
def get_vacancy_street():
    vacancy_street = request.args.get('vacancy-street', type=str, default='Ленинградская')
    with local_session() as db:
        result = db.query(
            func.count(Vacancy.name).label('vacancy_count')
        ).filter(Vacancy.address.like(f'%{vacancy_street}%')) \
        .order_by('vacancy_count') \
        .all()

        return jsonify([{
            'Количество_вакансий': r.vacancy_count
        } for r in result])


@app.route('/api/get-archived-vacancies', methods=['GET'])
def get_archived_vacancies():
    company_name = request.args.get('company-name', type=str, default='Пономарева Лимитед')
    with local_session() as db:
        result = db.query(
            Vacancy.name.label('vacancy_name'),
            Employer.name.label('company'),
            Post.name.label('post'),
            Vacancy.salary
        ).join(Employer) \
            .join(Post) \
            .filter(and_(
            Employer.name == company_name,
            Vacancy.status == VacancyStatus.archive
        )) \
        .order_by('company') \
        .all()

        return jsonify([{
            'Название_вакансии': r.vacancy_name,
            'Компания': r.company,
            'Должность': r.post,
            'Зарплата': r.salary
        } for r in result])


@app.route('/api/get-mean-salary', methods=['GET'])
def get_mean_salary():
    limit=request.args.get('limit', type=int, default=10)
    with local_session() as db:
        result = db.query(
            Employer.name.label('company'),
            func.round(func.avg(Vacancy.salary), 2).label('mean_salary')
        ).join(Employer) \
        .group_by(Employer.name) \
        .order_by(desc('mean_salary')) \
        .limit(limit) \
        .all()

        return jsonify([{
            'Компания': r.company,
            'Средняя_зп': r.mean_salary
        } for r in result])


@app.route('/api/get-worker-education-count', methods=['GET'])
def get_worker_education_count():
    with local_session() as db:
        result = db.query(
            func.count(func.distinct(Resume.worker_id)).label('count_worker')
        ).join(Worker)\
        .join(WorkerEducation)\
        .join(Education)\
        .filter(Education.type == EducationType.higher) \
        .order_by('count_worker') \
        .all()

        return jsonify([{
            'Количество_работников': r.count_worker
        } for r in result])


@app.route('/api/get-count-worker-place', methods=['GET'])
def get_count_worker_place():
    with local_session() as db:
        result = db.query(
            func.count(func.distinct(Worker.worker_id)).label('count_worker')
        ).join(WorkerWorkbook)\
        .join(Workbook)\
        .join(WorkbookEmployerWriting)\
        .join(WorkbookWriting)\
        .group_by(Worker.worker_id)\
        .having(func.count(func.distinct(WorkbookEmployerWriting.employer_id)) > 3) \
        .order_by('count_worker') \
        .all()
        count = len(result)

        return jsonify([{
            'Количество_работников': count
        }])


@app.route('/api/get-vacancy-salary-experience', methods=['GET'])
def get_vacancy_salary_experience():
    limit = request.args.get('limit', type=int, default=10)
    with local_session() as db:
        result = db.query(
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
        )) \
        .order_by('company') \
        .limit(limit) \
        .all()

        return jsonify([{
            'Название_вакансии': r.vacancy_name,
            'Компания': r.company,
            'Должность': r.post,
            'Зарплата': r.salary,
            'Опыт работы': r.experience
        } for r in result])


# @app.route('/api/get-post-name', methods=['GET'])
# def get_post_name():
#     post_name = request.args.get('post-name', type=str, default='Разработчик')
#     with local_session() as db:
#         result = db.query(
#             Post
#         ) \
#         .filter(Post.name.like(f'%{post_name}%')) \
#         .all()
#
#         return jsonify([{
#             'post_id': r.post_id,
#             'name': r.name
#         } for r in result])


@app.route('/api/get-post-name', methods=['GET'])
def get_post_name():
    post_name = request.args.get('post-name', type=str, default='Разработчик')
    with local_session() as db:
        query = f"SELECT * FROM post WHERE name LIKE '%{post_name}%'"
        result = db.execute(text(query))

        posts_data = [dict(row._mapping) for row in result]
        return jsonify(posts_data)


# @app.route('/api/get-requirement-id', methods=['GET'])
# def get_requirements_id():
#     requirement_id = request.args.get('requirement-id')
#     with local_session() as db:
#         result = db.query(
#             Requirement
#         ) \
#         .filter(Requirement.requirement_id == requirement_id) \
#         .all()
#         return jsonify([{
#             'requirement_id': r.requirement_id,
#             'description': r.description
#         } for r in result])


# @app.route('/api/get-requirement-id', methods=['GET'])
# def get_requirements_id():
#     requirement_id = request.args.get('requirement-id', type=int, default=10)
#
#     with local_session() as db:
#         query = text("SELECT * FROM requirement WHERE requirement_id = :requirement_id")
#         result = db.execute(query, {'requirement_id': requirement_id})
#
#         requirement_data = [dict(row._mapping) for row in result]
#         return jsonify(requirement_data)


@app.route('/api/get-requirement-id', methods=['GET'])
def get_requirements_id():
    requirement_id = request.args.get('requirement-id')
    with local_session() as db:
        query = f"SELECT * FROM requirement WHERE requirement_id = {requirement_id}"
        result = db.execute(text(query))

        requirement_data = [dict(row._mapping) for row in result]
        return jsonify(requirement_data)

@app.route('/')
def index():
    return '''
    <h1>Безопасные запросы</h1>
    <ul>
        <li><strong>1. Какие вакансии есть у данной компании?</strong><br>
            <a href="/api/get-vacancy-company?company-name=ЗАО «Одинцов Сидоров»">/api/get-vacancy-company?company-name=ЗАО «Одинцов Сидоров»</a></li>

        <li><strong>2. Какая вакансия подходит мне по названию?</strong><br>
            <a href="/api/get-vacancy-name?vacancy-name=Художник">/api/get-vacancy-name?vacancy-name=Художник</a></li>

        <li><strong>3. Сколько поблизости вакансий от меня (указание улицы)?</strong><br>
            <a href="/api/get-count-vacancy-street?vacancy-street=Ленинградская">/api/get-count-vacancy-street?vacancy-street=Ленинградская</a></li>

        <li><strong>4. Какие вакансии были помещены в архив у компании?</strong><br>
            <a href="/api/get-archived-vacancies?company-name=Пономарева Лимитед">/api/get-archived-vacancies?company-name=Пономарева Лимитед</a></li>

        <li><strong>5. Средняя ЗП каждого работодателя?</strong><br>
            <a href="/api/get-mean-salary?limit=20">/api/get-mean-salary?limit=20</a></li>

        <li><strong>6. Сколько работников ищут работу, имея высшее образование?</strong><br>
            <a href="/api/get-worker-education-count">/api/get-worker-education-count</a></li>

        <li><strong>7. Сколько работников имело более 3-х мест работы?</strong><br>
            <a href="/api/get-count-worker-place">/api/get-count-worker-place</a></li>

        <li><strong>8. Какие вакансии имеют ЗП более 100 000р и не требуют опыта работы?</strong><br>
            <a href="/api/get-vacancy-salary-experience?limit=20">/api/get-vacancy-salary-experience?limit=20</a></li>
    </ul>
    
    <h1>Небезопасные запросы</h1>
    <ul>
        <li><strong>Вывод названий должностей через прямое встраивание в LIKE</strong><br>
            <a href="/api/get-post-name?post-name=Разработчик">/api/get-post-name?post-name=Разработчик</a>
            <br><strong>SQL-инъекция в запрос</strong><br>
            <a href="/api/get-post-name?post-name=Разработчик'; SELECT * FROM post WHERE name LIKE 'Аналитик">/api/get-post-name?post-name=Разработчик'; SELECT * FROM post WHERE name LIKE 'Аналитик</a>
        </li>
        
        <li><strong>Вывод описаний требований через прямое встраивание в =</strong><br>
            <a href="/api/get-requirement-id?requirement-id=10">/api/get-requirement-id?requirement-id=10</a>
            <br><strong>SQL-инъекция в запрос</strong><br>
            <a href="/api/get-requirement-id?requirement-id=10; SELECT * FROM post WHERE name LIKE '%Аналитик%'">/api/get-requirement-id?requirement-id=10; SELECT * FROM post WHERE name LIKE '%Аналитик%</a>
        </li>

    </ul>
    '''


if __name__ == '__main__':
    app.run(debug=True, port=5000, use_reloader=True)