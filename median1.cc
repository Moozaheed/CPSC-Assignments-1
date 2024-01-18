#include <iostream>
using namespace std;

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
    int n;
    while (true) {
        cout << "Enter the size of the list (< 1 to quit): ";
        cin >> n;

        if (n < 1) {
            break;
        }

        int *Arr = new int[n];
        for (int i = 0; i < n; ++i) {
            cout << "Enter element " << i + 1 << ": ";
            cin >> Arr[i];
        }

        cout << "The median is " << median(Arr, n) << "." << std::endl;
        
        delete[] Arr;
    }
    return 0;
}
