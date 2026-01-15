def insert():
    first_string = input()
    second_string = input()
    return first_string, second_string


def get_end_row(first_string, second_string):
    cost_first = [0]
    for i in range(len(first_string)):
        cost_first.append(cost_first[i] + 1)
    cost_second = [1]

    for i in range(1, len(second_string) + 1):
        for j in range(1, len(first_string) + 1):
            add_value = 1
            if first_string[j - 1] == second_string[i - 1]:
                add_value = 0
            cost_second.append(min(cost_first[j - 1] + add_value, cost_second[j - 1] + 1, cost_first[j] + 1))
        cost_first = cost_second
        cost_second = [cost_first[0] + 1]
    return cost_first


def get_min_levinstein(first_string, second_string):
    if len(first_string) <= 1 or len(second_string) <= 1:
        return get_end_row(first_string, second_string)[-1]

    current_idx = 0
    if len(first_string) < len(second_string):
        first_left = first_string[:len(first_string) // 2]
        first_right = first_string[len(first_string) // 2 :]

        left_row = get_end_row(second_string, first_left)
        right_row = get_end_row(second_string[::-1], first_right[::-1])

        for i in range(len(second_string) + 1):
            if left_row[i] + right_row[-i - 1] < left_row[current_idx] + right_row[-current_idx - 1]:
                current_idx = i

        second_left = second_string[:current_idx]
        second_right = second_string[current_idx:]
    else:
        second_left = second_string[:len(second_string) // 2]
        second_right = second_string[len(second_string) // 2:]

        left_row = get_end_row(first_string, second_left)
        right_row = get_end_row(first_string[::-1], second_right[::-1])

        for i in range(len(first_string) + 1):
            if left_row[i] + right_row[-i - 1] < left_row[current_idx] + right_row[-current_idx - 1]:
                current_idx = i

        first_left = first_string[:current_idx]
        first_right = first_string[current_idx:]

    return get_min_levinstein(first_left, second_left) + get_min_levinstein(first_right, second_right)


def output(cost_value):
    print(cost_value)


def __main__():
    first_string, second_string = insert()
    cost_value = get_min_levinstein(first_string, second_string)
    output(cost_value)


if __name__ == '__main__':
    __main__()