/// ЛР09-Б. Динамические массивы. Вариант 36.
/// Задача:
/// В заданной квадратной матрице размера 2n×2n поменять местами значения элементов
/// строк области 3 и элементов столбцов области 1 (см. рисунок) с одинаковыми номерами.

#include <clocale>
#include <iostream>
#include <ctime>

using namespace std;

typedef int telem; // объявление типа элемента массива
typedef telem* tstr; // объявление типа "указатель на telem"
typedef tstr* tmatr; //тип "указатель на указатель на telem"

tmatr allocate_memory(int str, int col);
void free_memory(tmatr matrix, int str);
void fill_matrix_random_elems(tmatr matrix, int str, int col, int from, int to);
void print_matrix(tmatr matrix, int str, int col);
void do_permutation(tmatr matrix, int size);


int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int size = 0;
    cout << "Введите размер квадратной матрицы, который будет умножен на 2: ";
    cin >> size;
    size *= 2;

    int from_rand = 0;
    int to_rand = 0;
    cout << "Введите пределы генерирования случайных чисел.\n";
    cout << "От ";
    cin >> from_rand;
    cout << "До ";
    cin >> to_rand;

    tmatr matrix = allocate_memory(size, size);
    fill_matrix_random_elems(matrix, size, size, from_rand, to_rand);
    cout << "Матрица " << size << 'x' << size << " из случайных элементов:\n";
    print_matrix(matrix, size, size);

    do_permutation(matrix, size);
    cout << "Результат перестановки элементов из между 1 и 3 областями:\n";
    print_matrix(matrix, size, size);
    free_memory(matrix, size);
    return 0;
}


tmatr allocate_memory(int str, int col) {
    tmatr matrix = new tstr[str];
    for (int i = 0; i < str; ++i) {
        matrix[i] = new telem[col];
    }
    return matrix;
}

void free_memory(tmatr matrix, int str) {
    for (int i = 0; i < str; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fill_matrix_random_elems(tmatr matrix, int str, int col, int from, int to) {
    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = rand() % (to - from + 1) + from;
        }
    }
}

void print_matrix(tmatr matrix, int str, int col) {
    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void do_permutation(tmatr matrix, int size) {
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
