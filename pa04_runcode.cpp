#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int runcode(string s) {
    int answer = s.length();
    for (int i = 1; i <= s.length() / 2; i++) {
        int len = s.length();
        for (int j = 0; j < s.length(); j++) {
            for (int count = 0, z = i; j + z < s.length(); z += i) {
                if (s.substr(j, i) == s.substr(j + z, i))    count++;
                else {
                    len -= i * count;
                    if (count)     len += to_string(count + 1).length();
                    j += z - 1;
                    break;
                }
                if (j + z + i >= s.length()) {
                    len -= i * count;
                    len += to_string(count + 1).length();
                    j += z;
                }
            }
        }
        if (len < answer)    answer = len;
    }
    return answer;
}

int main() {
    cin.tie(0); 
    ios::sync_with_stdio(false);
    int N = 0;
    string  s;
    int* arr;
    cin >> N;
    cin.ignore();
    arr = new int[N];
    for (int j = 0; j < N; ++j) {
        getline(cin, s);
        arr[j] = runcode(s);
        s = "";
    }

    for (int i = 0; i < N; ++i) {
        cout << arr[i] << "\n";
    }
    delete[] arr;
    return 0;
}