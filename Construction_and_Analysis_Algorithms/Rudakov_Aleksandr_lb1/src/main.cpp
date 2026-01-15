#include <algorithm>
#include <iostream>
#include <vector>

int read() {
    int size_of_square;
    std::cin >> size_of_square;
    return size_of_square;
}

int find_smallest_divisor(int value) {
    int returned_value = 1;
    for (int i = 2; i <= value; i++) {
        if (value % i == 0) {
            returned_value = i;
            break;
        }
    }
    return returned_value;
}

struct SquaresInfo {
    int x;
    int y;
    int square_size;
} typedef SquaresInfo;

class Table {
private:
    std::vector<std::vector<int>> table;
    std::vector<SquaresInfo> squares;
    int size_of_square;
    int smallest_divisor;
    int min_number;
    int space;

    void paint(int x, int y, int size_square) {
        for (int i = x; i < x + size_square; i++) {
            for (int j = y; j < y + size_square; j++) {
                table[i][j] = 1;
            }
        }
    }

    void repaint(int x, int y, int size_square) {
        for (int i = x; i < x + size_square; i++) {
            for (int j = y; j < y + size_square; j++) {
                table[i][j] = 0;
            }
        }
    }

    bool check_availability(int x, int y, int size_square) {
        if (x + size_square > smallest_divisor || y + size_square > smallest_divisor) return false;
        for (int i = x; i < x + size_square; i++) {
            for (int j = y; j < y + size_square; j++) {
                if (table[i][j] != 0) return false;
            }
        }
        return true;
    }

    bool check_fullness() {
        if (space == 0) return true;
        return false;
    }

    void cmp_with_other(std::vector<SquaresInfo> current_squares) {
        if (current_squares.size() < min_number || min_number == smallest_divisor * smallest_divisor) {
            min_number = current_squares.size();
            squares = current_squares;
        }
    }

    void add_squares(int x, int y, int size_square, std::vector<SquaresInfo>& current_squares) {
        paint(x, y, size_square);
        current_squares.push_back(SquaresInfo{ x, y, size_square });
        space -= size_square * size_square;
    }

    void remove_squares(int x, int y, int size_square, std::vector<SquaresInfo>& current_squares) {
        repaint(x, y, size_square);
        current_squares.pop_back();
        space += size_square * size_square;
    }

    std::pair<int, int> find_place() {
        for (int i = 0; i < smallest_divisor; i++) {
            for (int j = 0; j < smallest_divisor; j++) {
                if (table[i][j] == 0) {
                    return std::make_pair(i, j);
                }
            }
        }
    }

    int calculate_max_size (int x, int y){
        int max_size = std::min(smallest_divisor - x + 1, smallest_divisor - y + 1);
        max_size = std::min(max_size, smallest_divisor - 1);
        max_size = std::min(max_size, (smallest_divisor / 2) + 1);
        return max_size;
    }

    void find_placement(std::vector<SquaresInfo>& current_squares) {
        std::pair<int, int> coordinate = find_place();
        int x = coordinate.first;
        int y = coordinate.second;
        int max_size = calculate_max_size(x, y);

        if (current_squares.size() + space / max_size > min_number) {
            return;
        }

        for (int current_size = max_size; current_size > 0; current_size--) {
            if (check_availability(x, y, current_size)) {
                add_squares(x, y, current_size, current_squares);
                if (check_fullness()) {
                    cmp_with_other(current_squares);
                }
                else {
                    find_placement(current_squares);
                }
                remove_squares(x, y, current_size, current_squares);
            }
        }
    }

    void start_place(std::vector<SquaresInfo>& current_squares) {
        if (smallest_divisor > 3) {
            int size_square = smallest_divisor / 2 + 1;
            add_squares(size_square - 1, size_square - 1, size_square, current_squares);
            add_squares(0, size_square, size_square - 1, current_squares);
            add_squares(size_square, 0, size_square - 1, current_squares);
        }
    }

public:
    Table(int size_of_square, int smallest_divisor) : size_of_square(size_of_square),
        smallest_divisor(smallest_divisor), min_number(smallest_divisor* smallest_divisor), space(smallest_divisor* smallest_divisor) {
        table.resize(smallest_divisor);
        for (int i = 0; i < smallest_divisor; i++) {
            table[i].resize(smallest_divisor);
            for (int j = 0; j < smallest_divisor; j++) {
                table[i][j] = 0;
            }
        }
    }

    void update_answer() {
        std::vector<SquaresInfo> current_squares;
        start_place(current_squares);
        find_placement(current_squares);
        int mul = size_of_square / smallest_divisor;
        for (int i = 0; i < min_number; i++) {
            squares[i].x = (squares[i].x + 1) * mul - (mul - 1);
            squares[i].y = (squares[i].y + 1) * mul - (mul - 1);
            squares[i].square_size *= mul;
        }
    }

    void print_answer() {
        update_answer();
        std::cout << min_number << '\n';
        for (int i = 0; i < min_number; i++) {
            std::cout << squares[i].x << ' ' << squares[i].y << ' ' << squares[i].square_size << '\n';
        }
    }

    ~Table() {
        for (int i = 0; i < smallest_divisor; i++) {
            table[i].clear();
        }
        table.clear();
        squares.clear();
    }
};

int main() {
    int size_of_squares = read();
    int smallest_divisor = find_smallest_divisor(size_of_squares);
    Table table = Table(size_of_squares, smallest_divisor);
    table.print_answer();
}