#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

void selectsort(int list[], int n, int start) {
    int least = start;
    int i;
    int min = list[start];
    if (n > start) {
        for (i = start; i < n; i++) {
            if (min > list[i]) {
                min = list[i];
                least = i;
            }
        }
        if (list[start] != min)
            swap(list[start], list[least]);

        selectsort(list, n, start + 1);
    }
}

int main(void) {
    int pass;
    int N = 0;
    int* arr;
    cin >> N >> pass;
    arr = new int[N+1];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    arr[N] == 0;
    int k = arr[pass - 1];
    selectsort(arr, N, 0);
    int sum = 0;

    if (pass != 0) {
        for (int i = 0; i < N; i++) {
            if (arr[i] == k) {
                swap(arr[i], arr[N]);
                k = i;
            }

        }
        for (int i = 0; i <= N; i++) {
            if (i != 0) {
                arr[i] = arr[i - 1] + arr[i];
            }
        }

        for (int i = 0; i <= N; i++) {
            if (i != k) {
                sum += arr[i];
            }
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            if (i != 0) {
                arr[i] = arr[i - 1] + arr[i];
            }
        }
        for (int i = 0; i < N; i++) {
            sum += arr[i];
        }
    }
    cout << sum;
    delete[] arr;
    return 0;
}