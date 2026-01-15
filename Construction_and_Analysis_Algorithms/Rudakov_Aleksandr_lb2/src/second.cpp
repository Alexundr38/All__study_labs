#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <limits>
#include <queue>

float FLOAT_MAX = std::numeric_limits<float>::max();

struct Edge {
    char vertex;
    float weight;
};

struct VertexInfo {
    char vertex;
    float f_score;
    float g_score;
    std::string way;
    bool operator>(const VertexInfo& other) const {
        return f_score > other.f_score;
    }
};

class AStarSearch {
    std::map<char, std::vector<Edge>> vertexes;
    std::map<char, VertexInfo> vertex_info;
    char start;
    char end;

public:

    void input() {
        std::string new_string;
        getline(std::cin, new_string);
        start = new_string[0];
        end = new_string[2];
        while (getline(std::cin, new_string)) {
            if (new_string == "") break;
            char new_start = new_string[0];
            char new_end = new_string[2];
            float value = std::stof(new_string.substr(4, new_string.size() - 1));
            if (vertexes.count(new_start) == 0) {
                vertexes[new_start] = std::vector<Edge>();
                vertex_info[new_start] = { new_start, FLOAT_MAX, FLOAT_MAX, "" };
            }
            if (vertexes.count(new_end) == 0) {
                vertexes[new_end] = std::vector<Edge>();
                vertex_info[new_end] = { new_end, FLOAT_MAX, FLOAT_MAX, "" };
            }
            vertexes[new_start].push_back({ new_end, value });
        }
        vertex_info[start] = { start, comp_heuristic_function(start, end), 0, std::string(1, start) };
    }


    void find() {
        std::priority_queue<VertexInfo, std::vector<VertexInfo>, std::greater<VertexInfo>> queue;
        queue.push(vertex_info[start]);
        
        while (!queue.empty()) {
            VertexInfo current = queue.top();
            queue.pop();

            if (current.vertex == end) return;

            for (auto& vertex : vertexes[current.vertex]) {
                float prior_distance = current.g_score + vertex.weight;

                if (prior_distance < vertex_info[vertex.vertex].g_score) {
                    vertex_info[vertex.vertex].g_score = prior_distance;
                    vertex_info[vertex.vertex].f_score = prior_distance + comp_heuristic_function(vertex.vertex, end);
                    vertex_info[vertex.vertex].way = current.way + vertex.vertex;

                    queue.push(vertex_info[vertex.vertex]);
                }

            }
        }
    }

    float comp_heuristic_function(char start_vertex, char end_vertex) {
        return abs(float(start_vertex - end_vertex));
    }

    void print() {
        std::cout << vertex_info[end].way << '\n';
    }
};

int main() {
    AStarSearch a_star_search;
    a_star_search.input();
    a_star_search.find();
    a_star_search.print();
}