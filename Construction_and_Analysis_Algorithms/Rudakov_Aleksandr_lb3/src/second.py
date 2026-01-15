import heapq
INT_MAX = 2147483647

class Matrix:
    def __init__(self, matrix, start_vertex):
        self.__matrix = matrix
        self.__start_vertex = start_vertex
        self.__size = len(matrix)
        self.__spanning_tree = []
        self.__way = []
        self.create_spanning_tree()

    def find_min_edges(self):
        min_weight = INT_MAX
        first = self.__start_vertex
        second = 0
        for i in range(self.__size):
            if self.__matrix[first][i] < min_weight and self.__matrix[first][i] != -1:
                min_weight = self.__matrix[first][i]
                second = i
        return first, second

    def create_spanning_tree(self):
        first, second = self.find_min_edges()
        self.__spanning_tree = [(first, second), (second, first)]
        heap = []
        used = [False for i in range(self.__size)]
        used[first] = True
        used[second] = True

        for i in range(self.__size):
            if self.__matrix[first][i] != -1 and i != second:
                heapq.heappush(heap, (self.__matrix[first][i], (first, i)))
            if self.__matrix[second][i] != -1 and i != first:
                heapq.heappush(heap, (self.__matrix[second][i], (second, i)))

        while used.count(False) > 0:
            current_value = heapq.heappop(heap)
            current_vertex = current_value[1][1]

            if not used[current_vertex]:
                used[current_vertex] = True
                self.__spanning_tree.append(current_value[1])
                self.__spanning_tree.append(current_value[1][::-1])

                for i in range(self.__size):
                    if self.__matrix[current_vertex][i] != -1 and (not used[i]):
                        heapq.heappush(heap, (self.__matrix[current_vertex][i], (current_vertex, i)))

    def create_vertexes(self):
        vertexes = []
        for i in range(self.__size):
            next_vertexes = []
            for j in (self.__spanning_tree):
                if j[0] == i:
                    next_vertexes.append(j[1])
            vertexes.append(next_vertexes)
        return vertexes

    def create_way(self):
        count = len(self.__spanning_tree)
        vertexes = self.create_vertexes()
        idx = self.__start_vertex
        way = [idx]
        self.__way = []

        while count > 0:
            flag = True
            for i in vertexes[idx]:
                if idx in vertexes[i]:
                    way.append(i)
                    flag = False
                    vertexes[idx].remove(i)
                    idx = i
                    break
            if flag:
                add_vertex = vertexes[idx][0]
                way.append(add_vertex)
                vertexes[idx].remove(add_vertex)
                idx = add_vertex
            count -= 1

        for i in way:
            if not i in self.__way:
                self.__way.append(i)
        self.__way += [self.__start_vertex]
        return self.__way

    def calculate_sum(self):
        sum = 0
        for i in range(len(self.__way) - 1):
            sum += self.__matrix[self.__way[i]][self.__way[i + 1]]
        return sum

def input_data():
    start_vertex = int(input())
    matrix = []
    add_data = list(map(float, input().split()))
    matrix.append(add_data)
    for i in range(len(add_data) - 1):
        matrix.append(list(map(float, input().split())))
    return matrix, start_vertex

def output_data(way, sum):
    print("{:.2f}".format(sum))
    print(' '.join(map(str, way)))

def main():
    matrix, start_vertex = input_data()
    ways = Matrix(matrix, start_vertex)
    way = ways.create_way()
    sum = ways.calculate_sum()
    output_data(way, sum)

if __name__ == '__main__':
    main()