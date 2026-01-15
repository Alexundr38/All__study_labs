#include <iostream>
#include <string>
#include <vector>

using namespace std;

void input(string& pattern, string& text) {
	cin >> pattern;
	cin >> text;
}

void find_prefix_func(string& pattern, vector<int>& prefix_func) {
	prefix_func.push_back(0);
	for (int cur_idx = 1; cur_idx < pattern.size(); cur_idx++) {
		int start_index = prefix_func[cur_idx - 1];
		while (start_index > 0 && pattern[start_index] != pattern[cur_idx]) {
			start_index = prefix_func[start_index - 1];
		}
		if (pattern[start_index] == pattern[cur_idx]) start_index++;
		prefix_func.push_back(start_index);
	}
}

int find_cyclic_shift(string& first, string& second) {
	if (first.size() != second.size()) return -1;
	vector<int> prefix_func;
	find_prefix_func(first, prefix_func);
	int current_idx = 0;
	int i = 0;
	while (i < second.size()) {
		if (first[current_idx] == second[i]) {
			current_idx++;
			i++;
		}
		else {
			if (current_idx != 0) current_idx = prefix_func[current_idx - 1];
			else i++;
		}
	}
	if (current_idx == i) return 0;
	int remains = i - current_idx;
	i = 0;
	while (i < remains) {
		if (first[current_idx] == second[i]) {
			current_idx++;
			i++;
		}
		else return -1;
	}
	return second.size() - remains;
}

void output(int idx) {
	cout << idx << '\n';
}


int main() {
	string first, second;
	input(first, second);
	int idx = find_cyclic_shift(first, second);
	output(idx);
}