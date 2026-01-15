#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <limits>

float FLOAT_MAX = std::numeric_limits<float>::max();

struct Edge {
    char vertex;
    float weight;
};

class GreedySearch {
    std::map<char, std::vector<Edge>> vertexes;
    std::map<char, bool> used;
    char start;
    char end;
    std::string way;

public:

    void input() {
        std::string new_string;
        getline(std::cin, new_string);
        start = new_string[0];
        end = new_string[2];
        while (getline(std::cin, new_string)) {
            if (new_string == "") break;
            char first = new_string[0];
            char second = new_string[2];
            float value = std::stof(new_string.substr(4, new_string.size() - 1));
            if (vertexes.count(first) == 0) {
                vertexes[first] = std::vector<Edge>();
                used[first] = true;
            }
            vertexes[first].push_back({ second, value });
        }
        used[end] = true;
    }

    void start_find() {
        used[start] = false;
        way.push_back(start);
        find(start);
    }

    bool find(char current) {
        std::string use_vert;
        while (true) {
            char min_vert = '\0';
            float min_val = FLOAT_MAX;
            for (auto& variant : vertexes[current]) {
                bool used_flag = false;
                for (char used_vert : use_vert) {
                    if (variant.vertex == used_vert) {
                        used_flag = true;
                        break;
                    }
                }
                if (used_flag) continue;
                if (min_val > variant.weight || min_val == variant.weight && variant.vertex == end) {
                    if (used[variant.vertex]) {
                        min_val = variant.weight;
                        min_vert = variant.vertex;
                    }
                }
            }
            if (min_vert == '\0') return false;
            used[min_vert] = false;
            way.push_back(min_vert);
            if (min_vert == end) return true;

            if (find(min_vert)) return true;
            else {
                way.pop_back();
                used[min_vert] = true;
                use_vert.push_back(min_vert);
            }
        }
    }

    void print() {
        std::cout << way << '\n';
    }

};

int main() {
    GreedySearch greedy_search;
    greedy_search.input();
    greedy_search.start_find();
    greedy_search.print();
}