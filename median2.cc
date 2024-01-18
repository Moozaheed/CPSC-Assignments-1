#include <iostream>
#include <algorithm>
using namespace std;

int* resize(int *A, int n) {
    int *newArr = new int[n + 1];

    for (int i = 0; i < n; ++i) {
        newArr[i] = A[i];
    }

    delete[] A;
    return newArr;
}

void sort(int *A, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

double median(int *A, int n) {
    sort(A, n);
    if (n % 2 == 0) 
        return ((A[n/2-1])+(A[n/2])) / 2.0;
    else
        return (A[n/2]);
}


int main() {
    int *Arr = nullptr;
    int size = 0;

    while (true) {
        cout << "Enter a positive integer (< 1 to quit): ";
        int num;
        cin >> num;

        if (num < 1) {
            break;
        }

        Arr = resize(Arr, size);
        Arr[size] = num;
        size++;

        cout << "The median so far is " << median(Arr, size) << "." << endl;
    }

    delete[] Arr;
    return 0;
}
