#include <iostream>

using namespace std;

template <typename Type>
Type** MemoryAllocationTwoDimensionalArr(int str, int col, Type default_value = 0) {
    Type** arr = new Type* [str];
    for (int i = 0; i < str; ++i) {
        arr[i] = new Type[col];
        // заполнение значениями по умолчанию
        for (int j = 0; j < col; ++j) {
            arr[i][j] = default_value;
        }
    }
    return arr;
}

template <typename Type>
void FreeMemoryTwoDimensionalArr(Type** arr, int str) {
    for (int i = 0; i < str; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

template <typename Type>
void PrintTwoDimensionalArr(Type** arr, int str, int col) {
    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    int num_str = 8;
    int num_col = 7;
    {
        // при вызове функции указываем тип данных, передаваемых в шаблон
        double** arr = MemoryAllocationTwoDimensionalArr<double>(num_str, num_col, 0.5);
        PrintTwoDimensionalArr(arr, num_str, num_col);
        FreeMemoryTwoDimensionalArr(arr, num_str);
    }
    cout << endl;
    {
        // при вызове функции указываем тип данных, передаваемых в шаблон
        int** arr = MemoryAllocationTwoDimensionalArr<int>(num_str, num_col);
        PrintTwoDimensionalArr(arr, num_str, num_col);
        FreeMemoryTwoDimensionalArr(arr, num_str);
    }
    cout << endl;
    {
        // при вызове функции указываем тип данных, передаваемых в шаблон
        char** arr = MemoryAllocationTwoDimensionalArr<char>(num_str, num_col, 'a');
        PrintTwoDimensionalArr(arr, num_str, num_col);
        FreeMemoryTwoDimensionalArr(arr, num_str);
    }
    return 0;
}