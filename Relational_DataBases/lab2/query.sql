SELECT
    e.name AS Компания,
    v.name AS Название_вакансии,
    p.name AS Должность,
    salary,
    address,
    experience,
    comment,
    status
FROM
    vacancy v
    JOIN employer e USING (employer_id)
    JOIN post p USING (post_id)
WHERE e.name = 'КиберПредсказания';

SELECT
    v.name AS Название_вакансии,
    e.name AS Комания,
    p.name AS Должность,
    salary
FROM
    vacancy v
    JOIN employer e USING (employer_id)
    JOIN post p USING (post_id)
WHERE v.name LIKE '%склад%';

SELECT
    COUNT(*) AS Количество_вакансий
FROM vacancy
WHERE address LIKE '%Варшавская%';

SELECT
    v.name AS Название_вакансии,
    e.name AS Компания,
    p.name AS Должность,
    salary,
    status
FROM
    vacancy v
    JOIN employer e USING (employer_id)
    JOIN post p USING (post_id)
WHERE
    status = 'В архиве' AND
    e.name = 'ОАО "Везем"';

SELECT
    e.name AS Компания,
    ROUND(AVG(v.salary), 2) AS Средняя_зарплата
FROM
    vacancy v
    JOIN employer e USING (employer_id)
GROUP BY e.name
ORDER BY 2 DESC;

SELECT
    COUNT(DISTINCT r.worker_id) AS Количество_работников
FROM
    resume r
    JOIN worker USING (worker_id)
    JOIN worker_education USING (worker_id)
    JOIN education e USING (education_id)
WHERE e.type = 'Высшее';

SELECT
    COUNT(DISTINCT w.worker_id) AS Количество_работников
FROM
    worker w
    JOIN worker_workbook USING (worker_id)
    JOIN workbook USING (workbook_id)
    JOIN worker_employer_writing wer USING (workbook_id)
GROUP BY w.worker_id
HAVING COUNT(DISTINCT wer.employer_id) > 3;

SELECT
    v.name AS Название_вакансии,
    e.name AS Компания,
    p.name AS Должность,
    salary,
    experience
FROM
    vacancy v
    JOIN employer e USING (employer_id)
    JOIN post p USING (post_id)
WHERE
    salary > 100000 AND
    (experience = 0 OR
    experience IS NULL);