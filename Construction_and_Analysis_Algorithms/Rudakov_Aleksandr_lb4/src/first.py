def insert():
    replace_cost, insert_cost, delete_cost = map(int, input().split())
    first_string = input()
    second_string = input()
    return replace_cost, insert_cost, delete_cost, first_string, second_string


def get_min_cost(replace_cost, insert_cost, delete_cost, first_string, second_string):
    cost = [[0]]
    for i in range(len(first_string)):
        cost[0].append(cost[0][i] + delete_cost)
    for i in range(len(second_string)):
        cost.append([cost[i][0] + insert_cost])

    for i in range(1, len(second_string) + 1):
        for j in range(1, len(first_string) + 1):
            add_value = replace_cost
            if first_string[j - 1] == second_string[i - 1]:
                add_value = 0
            cost[i].append(min(cost[i - 1][j - 1] + add_value, cost[i][j - 1] + delete_cost, cost[i - 1][j] + insert_cost))
    return cost[-1][-1]


def output(cost_value):
    print(cost_value)


def __main__():
    replace_cost, insert_cost, delete_cost, first_string, second_string = insert()
    cost_value = get_min_cost(replace_cost, insert_cost, delete_cost, first_string, second_string)
    output(cost_value)


if __name__ == '__main__':
    __main__()
