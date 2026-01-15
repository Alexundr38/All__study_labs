#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Vertex {
	vector <int> childs = {};
	int parent;
	bool is_pattern;
	int suff_link;
	char symb;
	int idx;
	int pattern_idx = -1;
	int pattern_len = -1;

	Vertex(int parent, bool is_pattern, int suff_link, char symb, int idx) :
		parent(parent), is_pattern(is_pattern), suff_link(suff_link), symb(symb), idx(idx) {};
};

struct Bohr {
	vector <Vertex*> vertexes;

	Bohr() {
		vertexes.push_back(new Vertex({ 0, true, 0, '\0', 0 }));
	}

	void add_pattern(string pattern, int pattern_idx) {
		int current_idx = 0;
		for (char symb : pattern) {
			bool is_find = false;
			for (int idx : vertexes[current_idx]->childs) {
				if (vertexes[idx]->symb == symb) {
					current_idx = vertexes[idx]->idx;
					is_find = true;
					break;
				}
			}
			if (!is_find) {
				Vertex* new_vertex = new Vertex( current_idx, false, -1, symb, vertexes.size());
				vertexes.push_back(new_vertex);
				vertexes[current_idx]->childs.push_back(new_vertex->idx);
				current_idx = new_vertex->idx;
			}
		}
		vertexes[current_idx]->is_pattern = true;
		vertexes[current_idx]->pattern_idx = pattern_idx;
		vertexes[current_idx]->pattern_len = pattern.size();
	}

	void add_suff_links() {
		queue<int> vertex_queue;
		vertex_queue.push(0);

		while (!vertex_queue.empty()) {
			int current_idx = vertex_queue.front();
			vertex_queue.pop();

			if (vertexes[current_idx]->parent == 0) {
				vertexes[current_idx]->suff_link = 0;
			}
			else {
				int parent_suff = vertexes[vertexes[current_idx]->parent]->suff_link;
				vertexes[current_idx]->suff_link = get_suff_link(parent_suff, vertexes[current_idx]->symb);
			}

			for (int child : vertexes[current_idx]->childs) {
				vertex_queue.push(child);
			}
		}
	}

	int get_suff_link(int current_idx, char symb) {
		for (int child : vertexes[current_idx]->childs) {
			if (vertexes[child]->symb == symb) {
				return child;
			}
		}

		if (current_idx == 0) return 0;

		return get_suff_link(vertexes[current_idx]->suff_link, symb);
	}

	int find_next_idx(int current_idx, char symb) {
		for (int child : vertexes[current_idx]->childs) {
			if (vertexes[child]->symb == symb) {
				return child;
			}
		}
		if (current_idx == 0) return 0;
		return find_next_idx(vertexes[current_idx]->suff_link, symb);
	}

	vector<pair<int, int>> find_indexes(string text) {
		vector<pair<int, int>> result;
		int current_idx = 0;

		for (int i = 0; i < text.size(); i++) {
			current_idx = find_next_idx(current_idx, text[i]);

			int check_idx = current_idx;
			while (check_idx != 0) {
				if (vertexes[check_idx]->is_pattern) {
					result.push_back(make_pair(i - vertexes[check_idx]->pattern_len + 2, vertexes[check_idx]->pattern_idx));
				}
				check_idx = vertexes[check_idx]->suff_link;
			}
		}

		return result;
	}
};

void input(string& text, vector<string>& patterns) {
	cin >> text;
	int n;
	cin >> n;
	string current_pattern;
	for (int i = 0; i < n; i++) {
		cin >> current_pattern;
		patterns.push_back(current_pattern);
	}
}

void add_data(Bohr& bohr, vector<string>& patterns) {
	for (int i = 0; i < patterns.size(); i++) {
		bohr.add_pattern(patterns[i], i + 1);
	}
	bohr.add_suff_links();
}

void output(vector<pair<int, int>> result) {
	sort(result.begin(), result.end());
	for (auto out_res: result) {
		cout << out_res.first << " " << out_res.second << "\n";
	}
}

int main() {
	Bohr bohr;
	string text;
	vector<string> patterns;

	input(text, patterns);
	add_data(bohr, patterns);

	vector<pair<int, int>> result = bohr.find_indexes(text);
	output(result);

	return 0;
}