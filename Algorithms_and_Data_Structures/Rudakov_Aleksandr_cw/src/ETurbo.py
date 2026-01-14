from typing import Union
from random import randint
from itertools import product
import time

MAX_SUB = 10000000
N_MAX = 100000

class Score:
    def __init__(self, score: int, names: list, right = None, left = None):
        self.score: int = score
        self.names: list = names
        self.right: Union[Score, None] = right
        self.left: Union[Score, None] = left
        self.height: int = 1

    def __str__(self):
        out = ''
        for name in self.names:
            out += f'Score: {self.score}, Name: {name}\n'
        return out[:-1]

    def out_str(self):
        return f'Score: {self.score}, Names: {', '.join(map(str, self.names))}'

def left_rotate(root_score: Union[Score, None]) -> Score:
    new_root = root_score.right
    temp = new_root.left
    new_root.left = root_score
    root_score.right = temp

    root_score.height = calc_height(root_score)
    new_root.height = calc_height(new_root)
    return new_root

def right_rotate(root_score: Union[Score, None]) -> Score:
    new_root = root_score.left
    temp_root = new_root.right
    new_root.right = root_score
    root_score.left = temp_root

    root_score.height = calc_height(root_score)
    new_root.height = calc_height(new_root)
    return new_root

def height(root_score: Union[Score, None]) -> int:
    if root_score is None:
        return 0
    return root_score.height

def calc_height(root_score: Union[Score, None]) -> int:
    return 1 + max(height(root_score.right), height(root_score.left))

def check_balance(root_score: Union[Score, None]) -> int:
    return height(root_score.right) - height(root_score.left)

def check_right_bigger(root_score: Union[Score, None]) -> bool:
    if height(root_score.right) >= height(root_score.left):
        return True
    return False

def check_left_bigger(root_score: Union[Score, None]) -> bool:
    if height(root_score.right) <= height(root_score.left):
        return True
    return False

def insert(new_score: int, new_name: str, root_score: Union[Score, None]) -> Score:
    if root_score is None:
        return Score(new_score, [new_name])
    if root_score.score > new_score:
        root_score.left = insert(new_score, new_name, root_score.left)
    elif root_score.score < new_score:
        root_score.right = insert(new_score, new_name, root_score.right)
    else:
        root_score.names.append(new_name)

    root_score.height = calc_height(root_score)
    balance_flag = check_balance(root_score)

    if balance_flag == 2:
        if check_right_bigger(root_score.right):
            root_score = left_rotate(root_score)
        else:
            root_score.right = right_rotate(root_score.right)
            root_score = left_rotate(root_score)
    elif balance_flag == -2:
        if check_left_bigger(root_score.left):
            root_score = right_rotate(root_score)
        else:
            root_score.left = left_rotate(root_score.left)
            root_score = right_rotate(root_score)

    return root_score

def find(root_score: Union[Score, None], find_score: int, min_sub = MAX_SUB) -> (Score, int):
    if root_score.score == find_score:
        return root_score, 0

    current_sub = root_score.score - find_score             # check current
    if abs(current_sub) <= abs(min_sub):
        min_sub = current_sub

    if root_score.score > find_score:
        if root_score.left is None:
            return root_score, min_sub

        left_root, left_sub = find(root_score.left, find_score, min_sub)        #check left
        current_sub = left_root.score - find_score
        if abs(current_sub) <= abs(left_sub):
            return left_root, current_sub

        return root_score, min_sub

    if root_score.score < find_score:
        if root_score.right is None:
            return root_score, min_sub

        right_root, right_sub = find(root_score.right, find_score, min_sub)  # check right
        current_sub = right_root.score - find_score
        if abs(current_sub) <= abs(right_sub):
            return right_root, current_sub

        return root_score, min_sub

def print_biggest(root_score: Union[Score, None], min_score: int) -> None:
    if root_score.left and root_score.score > min_score:
        print_biggest(root_score.left, min_score)
    if root_score.score > min_score:
        print(root_score)
    if root_score.right:
        print_biggest(root_score.right, min_score)

def post_order(root_score: Union[Score, None]) -> None:
    left, right = 'left: x', 'right: x'
    center = 'center: ' + root_score.out_str()
    if root_score.left:
        left = left[:-1] + root_score.left.out_str()
        post_order(root_score.left)
    if root_score.right:
        right = right[:-1] + root_score.right.out_str()
        post_order(root_score.right)
    print(f'h: {root_score.height}   {left} {center} {right}')

def find_replace(root_score: Union[Score, None]) -> (Score, Union[Score, None]):
    if root_score.left is None:
        if root_score.right is None:
            replace_score = Score(root_score.score, root_score.names)
            return replace_score, None
        replace_score, root_score.right = find_replace(root_score.right)
    replace_score, root_score.left = find_replace(root_score.left)
    return replace_score, root_score

def replace(root_score: Union[Score, None]) -> Union[Score, None]:
    if root_score.left is None:
        if root_score.right is None:
            return None
        return root_score.right
    if root_score.left.right is None:
        root_score.left.right = root_score.right
        return root_score.left
    replace_score, root_score.left.right = find_replace(root_score.left.right)
    replace_score.left = root_score.left
    replace_score.right = root_score.right
    return replace_score

def remove(root_score: Union[Score, None], remove_score: int) -> Union[Score, None]:
    if root_score is None:
        return root_score
    if root_score.score == remove_score:
        root_score = replace(root_score)
    elif root_score.score > remove_score:
        root_score.left = remove(root_score.left, remove_score)
    elif root_score.score < remove_score:
        root_score.right = remove(root_score.right, remove_score)
    if root_score is None:
        return root_score

    root_score.height = calc_height(root_score)
    balance_flag = check_balance(root_score)

    if balance_flag == 2:
        if check_right_bigger(root_score.right):
            root_score = left_rotate(root_score)
        else:
            root_score.right = right_rotate(root_score.right)
            root_score = left_rotate(root_score)
    elif balance_flag == -2:
        if check_left_bigger(root_score.left):
            root_score = right_rotate(root_score)
        else:
            root_score.left = left_rotate(root_score.left)
            root_score = right_rotate(root_score)

    return root_score

root_score = None

for i in range(N_MAX):
    score = randint(1, N_MAX)
    val = randint(1,4)
    name = ''.join(map(str, list(product('ABCD', repeat = randint(1, val)))[randint(0, val - 1)]))
    root_score = insert(score, name, root_score)

class game:
    def __init__(self, root_score: Union[Score, None], current_score: int = 0):
        self.__root_score: Union[Score, None] = root_score
        self.__current_score: int = current_score

    def start_game(self):
        self.__input_answer()

    def __random_value(self):
        self.__current_score = randint(1, N_MAX)

    def __input_value(self):
        value = input('- Please enter your score: ')
        flag = True
        for char in value:
            if not char.isdigit():
                flag = False
                break
        if flag:
            self.__current_score = int(value)
        else:
            print('Incorrect input. Please try again.')
            self.__input_value()

    def __new_game(self):
        print('Start game!')
        for i in range(3):
            time.sleep(0.3)
            print('.', end = '')
        print('\nGame over!')
        self.__input_value()
        print(f'You have scored {self.__current_score} points')
        near_score, sub = find(self.__root_score, self.__current_score)
        if sub == 0:
            print('The same result for the players:')
        else:
            print('Wow! There was no such result before')
            print('The nearest result for the players:')
        print(near_score)
        self.__input_answer(False)

    def __show_biggest(self):
        print('A list of results larger than yours:')
        print_biggest(self.__root_score, self.__current_score)

    def __add_result(self):
        name = input('Enter your nickname: ')
        self.__root_score = insert(self.__current_score, name, self.__root_score)
        print('Your result has been added to the list')

    def __input_answer(self, is_first = True):
        if not is_first:
            print('- To see all the results above yours, enter [y]\n- To add your result, enter [s]')
        print('- To create the game, enter [c]\n- To turn off the electricity, enter [q]')
        answer = input()
        if answer == 'c':
            self.__new_game()
        elif answer == 'y' and not is_first:
            self.__show_biggest()
            self.__input_answer(False)
        elif answer == 's' and not is_first:
            self.__add_result()
            self.__input_answer(True)
        elif answer != 'q':
            print('Incorrect answer. Please try again')
            self.__input_answer(is_first)

new_game = game(root_score)
new_game.start_game()

