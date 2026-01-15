#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <random>
#include <limits>
#include <chrono>

float FLOAT_MAX = std::numeric_limits<float>::max();
int MAX_EDGE_WEIGHT = 100;
double TOLERANCE = 0.01;

struct Edge {
    int vertex;
    float weight;
};

struct Way {
    float distance;
    std::string way;
};

class DijkstraSearch {
    std::map<int, std::vector<Edge>> vertexes;
    std::map<int, bool> used;
    std::map<int, Way> vertex_distance;
    int start;
    int count_vertex;
    float probability;

public:

    void generate_graph() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> int_dist(1, MAX_EDGE_WEIGHT);
        std::uniform_real_distribution<> real_dist(0, 1);

        for (int i = 0; i < count_vertex; i++) {
            int current_vertex = i;
            used[current_vertex] = true;
            vertex_distance[current_vertex] = { FLOAT_MAX, "" };
            for (int j = 0; j < count_vertex; j++) {
                int add_vertex = j;
                if (current_vertex != add_vertex){
                    double rand_value = real_dist(gen);
                    if ((probability - rand_value) > TOLERANCE) {
                        int weight = int_dist(gen);
                        if (vertexes.count(current_vertex) == 0) {
                            vertexes[current_vertex] = std::vector<Edge>();
                        }
                        vertexes[current_vertex].push_back({ add_vertex, float(weight) });
                        std::cout << current_vertex << " " << add_vertex << " " << weight << '\n';
                    }
                }
            }
        }
        vertex_distance[start] = { 0, std::to_string(start) };
    }

    void other_input(int count_vertex, float probability, int start) {
        this->count_vertex = count_vertex;
        this->probability = probability;
        this->start = start;
    }

    void input() {
        std::cin >> count_vertex >> probability >> start;
    }

    void start_find() {
        int current = find_min_vertex();
        while (current != -1) {
            find(current);
            current = find_min_vertex();
        }
    }

    void find(char current) {
        for (auto& variant : vertexes[current]) {
            if (vertex_distance[variant.vertex].distance == FLOAT_MAX ||
                vertex_distance[variant.vertex].distance > vertex_distance[current].distance + variant.weight) {
                vertex_distance[variant.vertex].distance = vertex_distance[current].distance + variant.weight;
                vertex_distance[variant.vertex].way = vertex_distance[current].way + "-" + std::to_string(variant.vertex);
            }
        }
        used[current] = false;
    }

    char find_min_vertex() {
        int min_vert = -1;
        float min_val = FLOAT_MAX;
        for (auto& vertex_info : vertex_distance) {
            if (vertex_info.second.distance < min_val && used[vertex_info.first]) {
                min_val = vertex_info.second.distance;
                min_vert = vertex_info.first;
            }
        }
        return min_vert;
    }


    void print() {
	std::cout << "=========\n";
        for (auto& vertex_info : vertex_distance) {
            std::cout << vertex_info.first << ": " << vertex_info.second.way << " " << vertex_info.second.distance << "\n";
        }
    }

};

int main() {
    DijkstraSearch dijkstra_search;
    dijkstra_search.input();
    dijkstra_search.generate_graph();
    dijkstra_search.start_find();
    dijkstra_search.print();
}