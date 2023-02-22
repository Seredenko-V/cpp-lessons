#include <iostream>

using namespace std;

int main() {
    int num_str = 2;
    int num_col = 7;
    int* matrix = new int[num_str * num_col];

    for (int i = 0; i < num_str; ++i) {
        for (int j = 0; j < num_col; ++j) {
            matrix[i * num_str + j] = j;
            cout << matrix[i * num_str + j] << ' ';
        }
        cout << endl;
    }

    delete[] matrix;
    return 0;
}