def insert():
    replace_cost, insert_cost, delete_cost = map(int, input().split())
    first_string = input()
    second_string = input()
    return replace_cost, insert_cost, delete_cost, first_string, second_string


def get_cost_matrix(replace_cost, insert_cost, delete_cost, first_string, second_string):
    cost = [[(0, (-1, -1), 'M')]]
    for i in range(len(first_string)):
        cost[0].append((cost[0][i][0] + delete_cost, (0, i), 'D'))
    for i in range(len(second_string)):
        cost.append([(cost[i][0][0] + insert_cost, (i, 0), 'I')])

    for i in range(1, len(second_string) + 1):
        for j in range(1, len(first_string) + 1):
            if first_string[j - 1] == second_string[i - 1]:
                cost[i].append((cost[i - 1][j - 1][0], (i - 1, j - 1), 'M'))
                continue
            current_value = min(cost[i - 1][j - 1][0] + replace_cost, cost[i][j - 1][0] + delete_cost, cost[i - 1][j][0] + insert_cost)

            if current_value == cost[i - 1][j - 1][0] + replace_cost:
                cost[i].append((current_value, (i - 1, j - 1), 'R'))
            elif current_value == cost[i][j - 1][0] + delete_cost:
                cost[i].append((current_value, (i, j - 1), 'D'))
            elif current_value == cost[i - 1][j][0] + insert_cost:
                cost[i].append((current_value, (i - 1, j), 'I'))
    return cost


def get_min_cost_way(cost_matrix):
    first_idx = len(cost_matrix) - 1
    second_idx = len(cost_matrix[0]) - 1
    answer_way = ""
    while first_idx != 0 or second_idx != 0:
        answer_way += cost_matrix[first_idx][second_idx][2]
        new_first_idx = cost_matrix[first_idx][second_idx][1][0]
        new_second_idx = cost_matrix[first_idx][second_idx][1][1]
        first_idx = new_first_idx
        second_idx = new_second_idx
    return answer_way[::-1]


def output(cost_value, first_string, second_string):
    print(cost_value)
    print(first_string)
    print(second_string)


def __main__():
    replace_cost, insert_cost, delete_cost, first_string, second_string = insert()
    cost_matrix = get_cost_matrix(replace_cost, insert_cost, delete_cost, first_string, second_string)
    cost_way = get_min_cost_way(cost_matrix)
    output(cost_way, first_string, second_string)

if __name__ == '__main__':
    __main__()