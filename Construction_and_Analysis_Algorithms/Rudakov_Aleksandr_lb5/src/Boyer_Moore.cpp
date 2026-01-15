#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void input(string& pattern, string& text) {
	cin >> pattern;
	cin >> text;
}

void create_suffix_table(string& pattern, map<int, int>& good_suffix) {
	for (int i = 1; i < pattern.size(); i++) {
		string suffix = pattern.substr(pattern.size() - i, i);
		good_suffix[i] = pattern.size();
		for (int j = pattern.size() - i - 1; j > -1; j--) {
			if (pattern.substr(j, i) == suffix) {
				good_suffix[i] -= (i + j);
				break;
			}
		}
	}
	good_suffix[pattern.size()] = pattern.size();
}

void create_symbols_table(string& pattern, map<char, int>& bad_symbols) {
	for (int i = 0; i < pattern.size(); i++) {
		bad_symbols[pattern[i]] = pattern.size() - i - 1;
	}
}

vector<int> do_boere_moore(string& pattern, string& text, map<int, int>& good_suffix, map<char, int>& bad_symbols) {
	int t_idx = pattern.size() - 1;
	int p_idx = pattern.size() - 1;
	vector<int> returned;
	if (pattern.size() <= text.size()) {
		while (t_idx < text.size()) {
			while (p_idx >= 0 && pattern[p_idx] == text[t_idx]) {
				p_idx--;
				t_idx--;
			}
			if (p_idx == -1) {
				returned.push_back(t_idx + 1);
				t_idx += pattern.size() + 1;
				p_idx = pattern.size() - 1;
			}
			else {
				int good = (pattern.size() - p_idx - 1) + good_suffix[pattern.size() - p_idx - 1];
				int bad = 0;
				if (bad_symbols.count(text[t_idx]) == 0) {
					bad = pattern.size();
				}
				else {
					bad = max(1, bad_symbols[text[t_idx]]);
				}
				int shift = max(good, bad);
				t_idx += shift;
				p_idx = pattern.size() - 1;
			}
		}
	}
	return returned;
}

void output(vector<int>& out) {
	if (out.size() > 0) {
		for (int i : out) {
			cout << i << ",";
		}
	}
	else cout << "-1";
	cout << "\n";
}

int main() {
	string pattern, text;
	input(pattern, text);
	map <int, int> good_suffix;
	create_suffix_table(pattern, good_suffix);
	map <char, int> bad_symbols;
	create_symbols_table(pattern, bad_symbols);
	vector<int> out = do_boere_moore(pattern, text, good_suffix, bad_symbols);
	output(out);
}