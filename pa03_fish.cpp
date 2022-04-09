#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int check(int list[], int N){
	for (int i = 0; i < N; i++){
		if(list[i] != i+1){
			return 0;
		}
	}
	return 1;
}
int flop(int list[], int a, int b, int N){
	int baked;
	int *arr = new int[N];
	copy(list,list+N, arr);
	reverse(arr+a, arr+b);
	for(int d=a; d<=b-1; d++){
		arr[d] = arr[d]*(-1);
	}
    baked=check(arr, N);
    if(baked == 1){
    	return 1;
	}
	return 0;
}
string flip(int list[], int N){
	int *arr = new int[N];
	for (int i = 0; i <N; i++) {
        for (int j = i+1; j<=N; j++){
        	if(flop(list,i,j, N) == 1){
        		return "one";
			}
		}
    }
    for (int i = 0; i <N; i++) {
        for (int j = i+1; j<=N; j++){
        	copy(list,list+N, arr);
			reverse(arr+i, arr+j);
			for(int d=i; d<=j-1; d++){
				arr[d] = arr[d]*(-1);
			}
            for (int a = 0; a <N; a++) {
                for (int b = a+1; b <=N; b++) {
                    if (flop(arr,a,b, N) == 1) {
                        return "two";
                    }
                }
            }
		}
	}
    delete[] arr;
    return "over";
}


int main(){
	int N = 0;
	string result;
    int** arr;
    cin >> N;
    arr = new int*[5];
    for(int j=0; j<5; j++){
    	arr[j] = new int[N];
    	for (int i = 0; i < N; i++) {
        	cin >> arr[j][i];
    	}
	}
	
	for(int j=0; j<5; j++){
		result = flip(arr[j], N);
    	cout << result << endl;
	}
    for(int j=0; j<5; j++){
    	delete[] arr[j];
	}
	delete[] arr;
	return 0;
}
