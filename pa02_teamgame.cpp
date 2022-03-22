#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

void quicksort(long long int quick[], long long int i, long long int j)
{
    if (i >= j) return;
    long long int pivot = quick[(i + j) / 2];
    long long int left = i;
    long long int right = j;

    while (left <= right)
    {
        while (quick[left] < pivot) left++;
        while (quick[right] > pivot) right--;
        if (left <= right)
        {
            swap(quick[left], quick[right]);
            left++; right--;
        }
    }
    quicksort(quick, i, right);
    quicksort(quick, left, j);
}

int main(void) {
    long long int pass;
    long long int i = 0;
    long long int N = 0;
    long long int* arr;
    cin >> N >> pass;
    arr = new long long int[N + 1];
    for (i = 0; i < N; i++) {
        cin >> arr[i];
    }
    arr[N] == 0;
    long long int k = arr[pass - 1];
    quicksort(arr, 0, N - 1);
    long long int sum = 0;

    if (pass != 0) {
        for (i = 0; i < N; i++) {
            if (arr[i] == k) {
                swap(arr[i], arr[N]);
                k = i;
            }
        }
        for (i = 0; i <= N; i++) {
            if (i != 0) {
                arr[i] = arr[i - 1] + arr[i];
            }
        }
        for (i = 0; i <= N; i++) {
            if (i != k) {
                sum += arr[i];
            }
        }
    }
    else {
        for (i = 0; i < N; i++) {
            if (i != 0) {
                arr[i] = arr[i - 1] + arr[i];
            }
        }
        for (i = 0; i < N; i++) {
            sum += arr[i];
        }
    }
    cout << sum;
    delete[] arr;
    return 0;
}