import copy
INT_MAX = 2147483647

class Matrix:
    def __init__(self, matrix):
        self.__matrix = matrix
        self.__size = len(matrix)
        self.__vertexes = []
        self.create_vertexes()

    def create_vertexes(self):
        self.__vertexes = []
        for i in range(self.__size):
            next_vertexes = []
            for j in range(self.__size):
                if (i != j and self.__matrix[i][j] != 0):
                    next_vertexes.append(j)
            self.__vertexes.append(next_vertexes)

    def find_way(self):
        used = [1] + [0 for x in range(self.__size - 1)]
        path = [0]

        path, min_value, flag = self.find(used, path, 0, 0, INT_MAX)
        self.print(path, min_value, flag)

    def print(self, path, min_value, flag):
        if flag:
            print(min_value)
            print(' '.join(map(str, path)))
        else:
            print("no path")

    def find(self, used, path, idx, cur_value, min_value):
        flag = False
        return_path = path
        for j in (self.__vertexes[idx]):
            if j == 0 and used.count(0) == 0:
                if cur_value + self.__matrix[idx][j] < min_value:
                    return path + [0], cur_value + self.__matrix[idx][j], True
                return path, cur_value + self.__matrix[idx][j], False
            if used[j] == 0 and cur_value + self.__matrix[idx][j] < min_value:
                used[j] = 1
                path.append(j)
                cur_value += self.__matrix[idx][j]
                new_path, new_min_value, new_flag = self.find(used, path, j, cur_value, min_value)
                if new_flag:
                    return_path = copy.copy(new_path)
                    min_value = new_min_value
                    flag = True
                used[j] = 0
                path.remove(j)
                cur_value -= self.__matrix[idx][j]
        return return_path, min_value, flag

def input_data():
    number = int(input())
    matrix = []
    for i in range(number):
        matrix.append(list(map(int, input().split())))
    return matrix

def main():
    matrix = input_data()
    ways = Matrix(matrix)
    ways.find_way()

if __name__ == '__main__':
    main()