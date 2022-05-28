#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;

int SIZE = 0;

bool is_palindrome(string s) {
    int N = s.size();
    int left = 0, right = N - 1;
    while (left <= right)
    {
        if (s[left++] != s[right--])return false;
    }
    return true;
}
bool similar_palindrome(string s, int left, int right, bool can_skip) {
    int skip = s.size();
    if (s[0] == s[s.size() - 1]) {
        if (left > right)return true;
        if (s[left] == s[right])return similar_palindrome(s, left + 1, right - 1, can_skip);
        else if (can_skip) {
            for (int i = 0; i <= skip; ++i) {
                if (max(similar_palindrome(s, left + i, right, false), similar_palindrome(s, left, right - i, false))) {
                    SIZE = i;
                    return true;
                }
            }
            return false;
        }
        else return false;
    }
    else return false;
}

int getans(string s) {
    if (is_palindrome(s))
        return s.size();
    else if (similar_palindrome(s, 1, s.size() - 2, 1))
        return s.size() - SIZE;

    return 0;
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N = 0;
    string  s;
    int* arr;
    int t;
    cin >> N;
    cin.ignore();
    arr = new int[N];
    for (int j = 0; j < N; ++j) {
        getline(cin, s);
        arr[j] = getans(s);
        s = "";
    }

    for (int i = 0; i < N; ++i) {
        cout << arr[i] << endl;
    }
    delete[] arr;
    return 0;
}