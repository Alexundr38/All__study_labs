INT_MAX = 2147483647


def find_way(city, path, cost, count, visited, matrix, best_cost, best_path):
    if count == len(matrix):
        return complete_path(city, path, cost, best_cost, best_path, matrix)

    for next_city in range(len(matrix)):
        if not visited[next_city]:
            best_cost, best_path = explore_next_city(city, next_city, path, cost, count, visited, matrix, best_cost, best_path)

    return best_cost, best_path


def complete_path(city, path, cost, best_cost, best_path, matrix):
    cost += matrix[city][path[0]]
    if cost < best_cost:
        best_cost = cost
        best_path = path + [path[0]]
    return best_cost, best_path


def explore_next_city(city, next_city, path, cost, count, visited, matrix, best_cost, best_path):
    new_cost = cost + matrix[city][next_city]
    if new_cost < best_cost:
        visited[next_city] = True
        best_cost, best_path = find_way(next_city, path + [next_city], new_cost, count + 1, visited, matrix, best_cost, best_path)
        visited[next_city] = False
    return best_cost, best_path


def find_with_branch_and_bound(matrix):
    matrix_size = len(matrix)
    visited = [False] * matrix_size
    best_cost = INT_MAX
    best_path = []

    visited[0] = True
    best_cost, best_path = find_way(0, [0], 0, 1, visited, matrix, best_cost, best_path)

    return best_path, best_cost


def input_data():
    number = int(input())
    matrix = []
    for i in range(number):
        matrix.append(list(map(int, input().split())))
        matrix[i][matrix[i].index(-1)] = INT_MAX
    return matrix


def output_data(answer_way, answer_value):
    print(' '.join(map(str, answer_way[:-1])))
    print("{:.1f}".format(answer_value))


def main():
    matrix = input_data()
    path, cost = find_with_branch_and_bound(matrix)
    output_data(path, cost)


if __name__ == "__main__":
    main()
