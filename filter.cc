#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int **allocate(int m, int n);
void deallocate(int **A, int m);
bool read_image(const char *filename, int &m, int &n, int **&img);
bool write_image(const char *filename, int m, int n, int **img, const char *prefix);
void process(int **img, int m, int n, int **output, int (*filter)(int A[5][5]));
int average(int A[5][5]);
int median(int A[5][5]);
int strange(int A[5][5]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " file.pgm" << endl;
        return 1;
    }

    int m, n, **img;
    if (!read_image(argv[1], m, n, img)) {
        cerr << "Cannot open " << argv[1] << " for reading." << endl;
        return 2;
    }

    int **output = allocate(m, n);

    cout << "Applying average filter." << endl;
    process(img, m, n, output, average);
    if (!write_image(argv[1], m, n, output, "avg")) {
        cerr << "Cannot write result." << endl;
        return 3;
    }

    cout << "Applying median filter." << endl;
    process(img, m, n, output, median);
    if (!write_image(argv[1], m, n, output, "med")) {
        cerr << "Cannot write result." << endl;
        return 3;
    }

    cout << "Applying strange filter." << endl;
    process(img, m, n, output, strange);
    if (!write_image(argv[1], m, n, output, "str")) {
        cerr << "Cannot write result." << endl;
        return 3;
    }

    deallocate(img, m);
    deallocate(output, m);

    return 0;
}

int **allocate(int m, int n) {
    int **A = new int *[m];
    for (int i = 0; i < m; ++i) {
        A[i] = new int[n];
    }
    return A;
}

void deallocate(int **A, int m) {
    for (int i = 0; i < m; ++i) {
        delete[] A[i];
    }
    delete[] A;
}

bool read_image(const char *filename, int &m, int &n, int **&img) {
    ifstream is(filename, ios::binary);
    if (!is) {
        return false;
    }

    string s;

    is >> s;
    is >> n >> m >> s;
    is.ignore(1024, '\n');
    img = allocate(m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            img[i][j] = is.get();
        }
    }
    return true;
}

bool write_image(const char *filename, int m, int n, int **img, const char *prefix) {
    string s = prefix;
    s += "-";
    s += filename;

    ofstream os(s.c_str(), ios::binary);
    if (!os) {
        return false;
    }
    os << "P5" << endl;
    os << n << " " << m << endl;
    os << 255 << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            os.put(static_cast<unsigned char>(img[i][j]));
        }
    }
    return true;
}

void process(int **img, int m, int n, int **output, int (*filter)(int A[5][5])) {
    int A[5][5];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i < 2 || i >= m - 2 || j < 2 || j >= n - 2) {
                output[i][j] = 0;
            } else {
                for (int k = 0; k < 5; k++) {
                    for (int l = 0; l < 5; l++) {
                        A[k][l] = img[i - 2 + k][j - 2 + l];
                    }
                }
                output[i][j] = filter(A);
            }
        }
    }
}

int average(int A[5][5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            sum += A[i][j];
        }
    }
    return sum / 25;
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

int median(int A[5][5]) {
    int Array[25];
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Array[k++] = A[i][j];
        }
    }
    sort(Array,k);
    return Array[12];
}

int strange(int A[5][5]) {
    return static_cast<int>((255.0 / 2040) * (-A[1][1] - 2 * A[2][1] - A[3][1] + A[1][3] + 2 * A[2][3] + A[3][3] + 1020) + 0.5);
}
