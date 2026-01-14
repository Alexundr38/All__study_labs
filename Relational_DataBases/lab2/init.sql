CREATE TABLE passport
(
    passport_id     SERIAL PRIMARY KEY,
    passport_number INT NOT NULL,
    passport_series INT NOT NULL,
    UNIQUE (passport_number, passport_series)
);

CREATE TABLE tin
(
    tin_id SERIAL PRIMARY KEY,
    tin    BIGINT UNIQUE NOT NULL
);

CREATE TABLE workbook
(
    workbook_id     SERIAL PRIMARY KEY,
    workbook_number INT UNIQUE NOT NULL,
    isue_date       DATE
);

CREATE TABLE worker
(
    worker_id   SERIAL PRIMARY KEY,
    passport_id INT  NOT NULL,
    tin_id      INT  NOT NULL,
    birthday    DATE NOT NULL,
    FOREIGN KEY (passport_id) REFERENCES passport (passport_id),
    FOREIGN KEY (tin_id) REFERENCES tin (tin_id)
);

CREATE TABLE worker_workbook
(
    worker_id   INT NOT NULL,
    workbook_id INT NOT NULL,
    PRIMARY KEY (worker_id, workbook_id),
    FOREIGN KEY (worker_id) REFERENCES worker (worker_id),
    FOREIGN KEY (workbook_id) REFERENCES workbook (workbook_id)
);

CREATE TYPE education_type AS ENUM
    (
        'Высшее',
        'Среднее'
        );

CREATE TABLE education
(
    education_id SERIAL PRIMARY KEY,
    name         VARCHAR(255)   NOT NULL,
    type         education_type NOT NULL
);

CREATE TABLE worker_education
(
    worker_id    INT  NOT NULL,
    education_id INT  NOT NULL,
    enroll_date  DATE NOT NULL,
    PRIMARY KEY (worker_id, education_id),
    FOREIGN KEY (worker_id) REFERENCES worker (worker_id),
    FOREIGN KEY (education_id) REFERENCES education (education_id)
);

CREATE TABLE post
(
    post_id SERIAL PRIMARY KEY,
    name    VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE resume
(
    resume_id SERIAL PRIMARY KEY,
    worker_id INT NOT NULL,
    post_id   INT NOT NULL,
    salary    DECIMAL(8, 2),
    FOREIGN KEY (worker_id) REFERENCES worker (worker_id),
    FOREIGN KEY (post_id) REFERENCES post (post_id)
);

CREATE TABLE skill
(
    skill_id    SERIAL PRIMARY KEY,
    description VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE resume_skill
(
    resume_id INT NOT NULL,
    skill_id  INT NOT NULL,
    PRIMARY KEY (resume_id, skill_id),
    FOREIGN KEY (resume_id) REFERENCES resume (resume_id),
    FOREIGN KEY (skill_id) REFERENCES skill (skill_id)
);

CREATE TABLE field_of_activity
(
    activity_id SERIAL PRIMARY KEY,
    name        VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE employer
(
    employer_id SERIAL PRIMARY KEY,
    activity_id INT          NOT NULL,
    name        VARCHAR(255) NOT NULL,
    photo_url   VARCHAR(255),
    description VARCHAR(255),
    FOREIGN KEY (activity_id) REFERENCES field_of_activity (activity_id)
);

CREATE TABLE presentation_file
(
    file_id     SERIAL PRIMARY KEY,
    employer_id INT          NOT NULL,
    name        VARCHAR(255) NOT NULL,
    url         VARCHAR(255) NOT NULL,
    FOREIGN KEY (employer_id) REFERENCES employer (employer_id)
);

CREATE TYPE writing_type AS ENUM
    (
        'Зачисление',
        'Увольнение',
        'Переход',
        'Изменение должности'
        );

CREATE TABLE workbook_writing
(
    writing_id  SERIAL PRIMARY KEY,
    type        writing_type NOT NULL,
    date        DATE         NOT NULL,
    description VARCHAR(255)
);

CREATE TABLE worker_employer_writing
(
    writing_id  INT NOT NULL,
    workbook_id INT NOT NULL,
    employer_id INT NOT NULL,
    PRIMARY KEY (writing_id, workbook_id, employer_id),
    FOREIGN KEY (writing_id) REFERENCES workbook_writing (writing_id),
    FOREIGN KEY (workbook_id) REFERENCES workbook (workbook_id),
    FOREIGN KEY (employer_id) REFERENCES employer (employer_id)
);

CREATE TYPE vacancy_status AS ENUM
    (
        'Активна',
        'В архиве',
        'Удалена'
        );

CREATE TABLE vacancy
(
    vacancy_id  SERIAL PRIMARY KEY,
    post_id     INT            NOT NULL,
    employer_id INT            NOT NULL,
    name        VARCHAR(255)   NOT NULL,
    address     VARCHAR(255)   NOT NULL,
    salary      DECIMAL(8, 2)  NOT NULL,
    experience  INT,
    comment     VARCHAR(255),
    status      vacancy_status NOT NULL,
    FOREIGN KEY (post_id) REFERENCES post (post_id),
    FOREIGN KEY (employer_id) REFERENCES employer (employer_id)
);

CREATE TABLE requirement
(
    requirement_id SERIAL PRIMARY KEY,
    description    VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE vacancy_requirement
(
    vacancy_id     INT NOT NULL,
    requirement_id INT NOT NULL,
    PRIMARY KEY (vacancy_id, requirement_id),
    FOREIGN KEY (vacancy_id) REFERENCES vacancy (vacancy_id),
    FOREIGN KEY (requirement_id) REFERENCES requirement (requirement_id)
);

CREATE TABLE condition
(
    condition_id SERIAL PRIMARY KEY,
    description  VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE vacancy_condition
(
    vacancy_id   INT NOT NULL,
    condition_id INT NOT NULL,
    PRIMARY KEY (vacancy_id, condition_id),
    FOREIGN KEY (vacancy_id) REFERENCES vacancy (vacancy_id),
    FOREIGN KEY (condition_id) REFERENCES condition (condition_id)
);


