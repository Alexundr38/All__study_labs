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
	vector <int> idx_in_text;

	Vertex(int parent, bool is_pattern, int suff_link, char symb, int idx) :
		parent(parent), is_pattern(is_pattern), suff_link(suff_link), symb(symb), idx(idx) {};
};

struct Bohr {
	vector <Vertex*> vertexes;

	Bohr() {
		vertexes.push_back(new Vertex({ 0, true, 0, '\0', 0 }));
	}

	void add_pattern(string pattern, int idx_in_text, int pattern_idx) {
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
				Vertex* new_vertex = new Vertex(current_idx, false, -1, symb, vertexes.size());
				vertexes.push_back(new_vertex);
				vertexes[current_idx]->childs.push_back(new_vertex->idx);
				current_idx = new_vertex->idx;
			}
		}
		vertexes[current_idx]->is_pattern = true;
		vertexes[current_idx]->pattern_idx = pattern_idx;
		vertexes[current_idx]->pattern_len = pattern.size();
		vertexes[current_idx]->idx_in_text.push_back(idx_in_text);
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

	vector<int> find_indexes(string text) {
		int current_idx = 0;
		vector<int> count_patterns(text.size(), 0);

		for (int i = 0; i < text.size(); i++) {
			current_idx = find_next_idx(current_idx, text[i]);

			int check_idx = current_idx;
			while (check_idx != 0) {
				if (vertexes[check_idx]->is_pattern) {
					for (int j = 0; j < vertexes[check_idx]->idx_in_text.size(); j++) {
						int add_idx = i  - (vertexes[check_idx]->pattern_len - 1) - vertexes[check_idx]->idx_in_text[j];
						if (add_idx >= 0) {
							count_patterns[add_idx] += 1;
						}
					}
				}
				check_idx = vertexes[check_idx]->suff_link;
			}
		}

		return count_patterns;
	}
};


int input(string& text, vector<pair<string, int>>& patterns) {
	cin >> text;
	string pattern;
	cin >> pattern;
	char mask;
	cin >> mask;
	string current_pattern = "";
	for (int i = 0; i < pattern.size(); i++) {
		if (pattern[i] == mask) {
			if (current_pattern != "") {
				patterns.push_back(make_pair(current_pattern, i - current_pattern.size()));
			}
			current_pattern = "";
		}
		else {
			current_pattern += pattern[i];
		}
	}
	if (current_pattern != "") {
		patterns.push_back(make_pair(current_pattern, pattern.size() - current_pattern.size()));
	}
	return pattern.size();
}

void add_data(Bohr& bohr, vector<pair<string, int>>& patterns) {
	for (int i = 0; i < patterns.size(); i++) {
		bohr.add_pattern(patterns[i].first, patterns[i].second, i + 1);
	}
	bohr.add_suff_links();
}

vector<int> preprocessing(vector<int> pre_result, int pattern_count, int pattern_size) {
	vector <int> result;
	for (int i = 0; i < pre_result.size(); i++) {
		if (pre_result[i] == pattern_count && i + pattern_size <= pre_result.size()) {
			result.push_back(i + 1);
		}
	}
	return result;
}

void output(vector<int> result) {
	for (int out: result) {
		cout << out << '\n';
	}
}

int main() {
	Bohr bohr;
	string text;
	vector<pair<string, int>> patterns;
	int pattern_size = input(text, patterns);

	add_data(bohr, patterns);

	vector<int> pre_result = bohr.find_indexes(text);
	vector<int> result = preprocessing(pre_result, patterns.size(), pattern_size);

	output(result);

	return 0;
}