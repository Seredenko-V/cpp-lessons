/*******************************************************************************
    Работа с динамической памятью
*******************************************************************************/

#include <iostream>

using namespace std;

int main() {
    int str = 5;
    int stolb = 7;

    // выделили память под двумерный массив
    int** arr = new int*[str];
    for (int i = 0; i < stolb; ++i) {
        arr[i] = new int[stolb];
    }

    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < stolb; ++j) {
            arr[i][j] = 0;
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }

    // освободили память под двумерный массив
    for (int i = 0; i < str; ++i) {
        delete[] arr[i];
    }

    return 0;
}