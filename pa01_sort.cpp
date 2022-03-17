#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int quickcount = 0;
int heapcount = 0;
void selectsort(int list[], int n, int start, int pass) {
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
        if(list[start] != min)
            swap(list[start], list[least]);
        for (int i = 0; i < n; i++) {
            if ((start+1) == pass) {
                cout << list[i] << endl;
            }
        }
        selectsort(list, n, start + 1, pass);
    }
}
void updateheap(int list[], int n, int pass) {
    if (heapcount == pass) {
        for (int i = 0; i <=n ; i++) {
            cout << list[i] << endl;
        }
    }
    swap(list[0], list[n]);
    int root = 0;
    int child = 1;
    do {
        child = 2 * root + 1;
        if (list[child] > list[child + 1] && child < n - 1) {
            child++;
        }
        if (list[root] > list[child] && child < n) {
            swap(list[root], list[child]);
        }
        root = child;
    } while (child < n);
    heapcount++;
    updateheap(list, n - 1, pass);
}
void heapsort(int list[], int n, int pass) {
    for (int i = 1; i < n; i++) {
        int child = i;
        do {
            int root = (child - 1) / 2;
            if (list[root] > list[child]) {
                swap(list[root], list[child]);
            }
            child = root;
        } while (child != 0);
    }
    
    updateheap(list, n - 1, pass);
}

int partition(int list[], int left, int right) {
    int pivot;
    int low, high;

    low = left;
    high = right;
    pivot = list[left];

    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);
        do {
            high--;
        } while (high >= left && list[high] > pivot);
        if (low < high) {
            swap(list[low], list[high]);
        }
    } while (low < high);
    swap(list[left], list[high]);
    return high;
}
void quicksort(int list[], int left, int right, int pass, int n) {
    if (left < right) {
        int q = partition(list, left, right);
        quickcount++;
        if (quickcount == pass) {
            for (int i = 0; i < n; i++) {
                cout << list[i] << endl;
            }
        }
        quicksort(list, left, q - 1, pass, n);
        quicksort(list, q + 1, right, pass, n);
    }
}
int main(void) {
    int sortkind, pass;
    int N=0;
    int* arr;
    cin >> sortkind >> pass;
    cin >> N;
    arr = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    switch (sortkind) {
        case 1:
            selectsort(arr, N, 0, pass);
            break;
        case 2:
            heapsort(arr, N, pass);
            heapcount = 0;
            break;
        case 3:
            quicksort(arr, 0, N, pass, N);
            quickcount = 0;
            break;
        default:
            break;
    }
    
    delete[] arr;
	return 0;
}
