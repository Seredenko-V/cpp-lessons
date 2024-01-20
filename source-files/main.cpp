/// ЛР09-Б. Динамические массивы. Вариант 36.
/// Задача:
/// В заданной квадратной матрице размера 2n×2n поменять местами значения элементов
/// строк области 3 и элементов столбцов области 1 (см. рисунок) с одинаковыми номерами.

#include <clocale>
#include <iostream>
#include <cassert>

using namespace std;

typedef int telem; // объявление типа элемента массива
typedef telem* tstr; // объявление типа "указатель на telem"
typedef tstr* tmatr; //тип "указатель на указатель на telem"

tmatr AllocateMemory(int str, int col);
void FreeMemory(tmatr matrix, int str);
void PrintMatrix(tmatr matrix, int str, int col);
void DoPermutation(tmatr matrix, int size);

namespace tests {
    void Test() {
        {
            constexpr uint32_t kSize = 4u;
            telem static_matr[kSize][kSize]{
                {1,2,3,4},
                {5,6,7,8},
                {9,0,1,2},
                {3,4,5,6}
            };
            telem expected_matr[kSize][kSize]{
                {1,8,3,4},
                {5,6,7,2},
                {9,0,1,2},
                {3,4,5,6}
            };
            tmatr dynamic_matr = AllocateMemory(kSize, kSize);
            for (int i = 0; i < kSize; ++i) {
                for (int j = 0; j < kSize; ++j) {
                    dynamic_matr[i][j] = static_matr[i][j];
                }
            }
            DoPermutation(dynamic_matr, kSize);
            for (int i = 0; i < kSize; ++i) {
                for (int j = 0; j < kSize; ++j) {
                    assert(dynamic_matr[i][j] == expected_matr[i][j]);
                }
            }
            FreeMemory(dynamic_matr, kSize);
        }{
            constexpr uint32_t kSize = 6u;
            telem static_matr[kSize][kSize]{
                {1,2,3,4,5,6},
                {7,8,9,0,1,2},
                {3,4,5,6,7,8},
                {9,0,1,2,3,4},
                {5,6,7,8,9,0},
                {1,2,3,4,5,6}
            };
            telem expected_matr[kSize][kSize]{
                {1,2,8,4,5,6},
                {7,8,7,0,1,2},
                {3,4,5,6,9,3},
                {9,0,1,2,3,4},
                {5,6,7,8,9,0},
                {1,2,3,4,5,6}
            };
            tmatr dynamic_matr = AllocateMemory(kSize, kSize);
            for (int i = 0; i < kSize; ++i) {
                for (int j = 0; j < kSize; ++j) {
                    dynamic_matr[i][j] = static_matr[i][j];
                }
            }
            DoPermutation(dynamic_matr, kSize);
            for (int i = 0; i < kSize; ++i) {
                for (int j = 0; j < kSize; ++j) {
                    assert(dynamic_matr[i][j] == expected_matr[i][j]);
                }
            }
            FreeMemory(dynamic_matr, kSize);
        }
        cerr << "Test passed\n";
    }
} // namespace tests;


int main() {
    setlocale(LC_ALL, "Russian");
    tests::Test();
    return 0;
}


tmatr AllocateMemory(int str, int col) {
    tmatr matrix = new tstr[str];
    for (int i = 0; i < str; ++i) {
        matrix[i] = new telem[col];
    }
    return matrix;
}

void FreeMemory(tmatr matrix, int str) {
    for (int i = 0; i < str; ++i) {
        delete[] matrix[i];
    }
    delete matrix;
}

void PrintMatrix(tmatr matrix, int str, int col) {
    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void DoPermutation(tmatr matrix, int size) {
    if (size % 2) { // нечетное кол-во строк и столбцов
        return;
    }
    for (int i1 = 0; i1 < size / 2 - 1; ++i1) {
        for (int j1 = i1 + 1; j1 < size / 2; ++j1) {
            const int j3 = size - 1 - i1;
            telem tmp = matrix[i1][j1];
            matrix[i1][j1] = matrix[j1][j3];
            matrix[j1][j3] = tmp;
        }
    }
}
