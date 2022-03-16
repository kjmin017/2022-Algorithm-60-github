#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

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
        selectsort(list, n, start + 1, pass);
    }
    else {
        for (int i = 0; i < n; i++) {
            if ((i + 1) % pass == 0) {
                cout << list[i] << endl;
            }
        }
    }
}
void heapsort() {

}
void mergesort() {

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
            break;
        case 3:
            break;
        default:
            break;
    }
    
    delete[] arr;
	return 0;
}
