#include <iostream>
#include <string>
#include <vector>

using namespace std;

void input(string &pattern, string &text) {
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

vector<int> find_index(string& pattern, string& text) {
	vector<int> prefix_func;
	find_prefix_func(pattern, prefix_func);
	int current_idx = 0;
	vector <int> returned_idx;
	int i = 0;
	while (i < text.size()) {
		if (pattern[current_idx] == text[i]) {
			current_idx++;
			if (current_idx == pattern.size()) {
				returned_idx.push_back(i - current_idx + 1);
				current_idx = prefix_func[current_idx - 1];
			}
			i++;
		}
		else {
			if (current_idx != 0) current_idx = prefix_func[current_idx - 1];
			else i++;
		}
	}
	return returned_idx;
}

void output(vector<int>& finded_idx) {
	string out;
	for (int i : finded_idx) {
		out += to_string(i) + ",";
	}
	if (out.size() > 0) {
		out.pop_back();
		cout << out << '\n';
	}
	else {
		cout << "-1\n";
	}
}


int main() {
	string pattern, text;
	input(pattern, text);
	vector<int> finded_idx = find_index(pattern, text);
	output(finded_idx);
}