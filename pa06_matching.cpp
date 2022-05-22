#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX_SIZE = 256;

int RabinKarp(string text, string pattern) {
	int textSize = text.size();
	int patternSize = pattern.size();
	int textHash = 0, patternHash = 0, power = 1;
	int count = 0;
	for (int i = 0; i <= textSize - patternSize; i++) {
		if (i == 0) {
			for (int j = 0; j < patternSize; j++) { 
				textHash = textHash + (text[patternSize - 1 - j] % 997) * power;
				patternHash = patternHash + (pattern[patternSize - 1 - j] % 997) * power;
				power *= 2;
			}
		}
		else { 
			textHash = 2 * (textHash - text[i - 1] * (power / 2)) + text[i + patternSize - 1];
		}
		if (textHash == patternHash) { 
			bool finished = true;
			for (int j = 0; j < patternSize; j++) {
				if (text[j + i] != pattern[j]) { 
					finished = false;
					break;
				}
				count++;
			}
			if (finished) return count + 1;
			
		}
		count++;
	}
	return 0;
}
vector<int> Fail(string pattern) {
	int m = pattern.length();
	vector<int> pi(m); 
	pi[0] = 0;
	for (int i = 1, j = 0; i < m; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {
			j = pi[j - 1];
		}
		if (pattern[i] == pattern[j])
			pi[i] = ++j;
	}
	return pi;
}

int KMP(string text, string pattern) {
	int m = pattern.length();
	int n = text.length();
	vector<int> pos;
	vector<int> pi = Fail(pattern);
	int count = 0;
	for (int i = 0, j = 0; i < n; i++) {
		while (j > 0 && text[i] != pattern[j]) {
			j = pi[j - 1];
		}
		if (text[i] == pattern[j]) {
			if (j == m - 1) {
				pos.push_back(i - m + 1);
				j = pi[j];
				return count;
			}
			else j++;
		}
		count++;
	}
	
	return 0;
}

vector<int> make_to_bad_character_tb(const string pattern)
{
	const int p_size = pattern.size();
	vector<int> bc_tb(MAX_SIZE, p_size);

	for (int i = 0; i < p_size; ++i)
		bc_tb[(int)pattern[i]] = i;

	return bc_tb;
}

vector<int> make_to_gs_tb(const string pattern)
{
	const int p_size = pattern.size();

	int pattern_point = p_size;
	int suffix_point = pattern_point + 1;

	vector<int> suf_tb(p_size + 1, 0);
	suf_tb[pattern_point] = suffix_point;

	vector<int> skip_tb(p_size + 1, 0);

	while (pattern_point > 0){
		while (suffix_point <= p_size && pattern[pattern_point - 1] != pattern[suffix_point - 1]){
			if (skip_tb[suffix_point] == 0)
				skip_tb[suffix_point] = suffix_point - pattern_point;
			suffix_point = suf_tb[suffix_point];
		}
		suf_tb[--pattern_point] = --suffix_point;
	}

	suffix_point = suf_tb[0];
	while (pattern_point < p_size){
		if (skip_tb[pattern_point] == 0)
			skip_tb[pattern_point] = suffix_point;
		if (pattern_point++ == suffix_point)
			suffix_point = suf_tb[suffix_point];
	}
	return skip_tb;
}

int BM(const vector<int> bc_tb, const vector<int> gs_tb, const string H, const string pattern){
	const int h_size = H.size();
	const int p_size = pattern.size();
	int count = 0;
	int begin = 0;

	while (begin <= h_size - p_size){
		int matched = p_size;

		while (matched > 0 && pattern[matched - 1] == H[begin + (matched - 1)]){
			--matched;
		}

		if (matched == 0)
			return count;

		if (bc_tb[H[begin + matched]] != p_size){
			begin += max(matched - bc_tb[H[begin + matched]],
				gs_tb[matched]);
		}
		else{
			begin += max(gs_tb[matched], matched);
		}
		count++;
	}

	return -1;
}

void printresult(int a, int b, int c) {
	cout << a << " " << b << " " << c ;
}
int main() {
	int P, T = 0;
	int a, b, c;
	string sub;
	string pattern = "";
	string text = "";
	cin >> P;
	for (int j = 0; j < P; ++j) {
		cin >> sub;
		pattern += sub;
	}

	cin >> T;
	for (int j = 0; j < T; ++j) {
		cin >> sub;
		text += sub;
	}
	
	a = RabinKarp(text, pattern);
	b = KMP(text, pattern);

	const vector<int> bc_table = make_to_bad_character_tb(pattern);
	const vector<int> gs_table = make_to_gs_tb(pattern);
	c = BM(bc_table, gs_table, text, pattern);
	printresult(a, b, c);

	
	return 0;
}
