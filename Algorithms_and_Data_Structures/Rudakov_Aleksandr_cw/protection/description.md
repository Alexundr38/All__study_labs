# Рудаков Александр Леонидович. Вариант 8
## date :: 25.11.2024 
## grade :: хорошо

Для задачи требовался быстрый поиск, поэтому стоял выбор между хэш-таблице и 
АВЛ-деревом. Так как кроме быстрого поиска требовалась упорядоченность 
элементов, была выбрана структура АВЛ-дерева.

[Код работы](../src/)

## Задание на защиту

Протестировать работоспособность структуры при замене флагов поворота дерева
с 2 на 32. Добавить функцию вывода результатов меньше данного в порядке невозрастания.

## Выполнение задания
### Идея выполнения

Для вывода результатов, меньших данного требуется сделать обратный
in-order обход дерева, проходящий, по левым веткам текущих поддеревьев,
идущий в сторону уменьшения.

### Исполнение в коде

Для тестирования работоспособности структуры при замене флагов поворота
в функции insert была переделана и протестирована часть:
```python
if balance_flag == 32:
    if check_right_bigger(root_score.right):
        root_score = left_rotate(root_score)
    else:
        root_score.right = right_rotate(root_score.right)
        root_score = left_rotate(root_score)
elif balance_flag == -32:
    if check_left_bigger(root_score.left):
        root_score = right_rotate(root_score)
    else:
        root_score.left = left_rotate(root_score.left)
        root_score = right_rotate(root_score)
```
При проверке результата оказалось, что упорядоченность АВЛ-дерева сохраняется,
но теряется баланс высот.

Для вывода результатов, меньших поданного, добавлена функция:
```python
def print_smallest(root_score: Union[Score, None], min_score: int) -> None:
    if root_score.right and root_score.score < min_score:
        print_smallst(root_score.right, min_score)
    if root_score.score < min_score:
        print(root_score)
    if root_score.left:
        print_smallest(root_score.left, min_score)
```
