/// ЛР04. Статические одномерные массивы. Вариант 36.
/// Задача:
/// Дан целочисленный массив a0, a1,…, am-1, среди элементов которого
/// могут быть элементы с равными значениями.
/// Построить новый массив, включив в него из каждой группы равных между
/// собой элементов только один, выбросив все остальные, и сохранив
/// исходный порядок их следования.
/// ==========================================================================
/// Дисклеймер:
/// Вырвиглазное решение, которое не следует никому показывать, кроме препода.
/// На практике за такое написание кода сжигают на костре.
/// Тесты не написаны ровно по той же причине, чтобы дед не гневался.
/// Правильно писать так https://google.github.io/styleguide/cppguide.html
/// ==========================================================================

#include <iostream>

using namespace std;

const int RAZ = 10;		//предельный размер массива
typedef int telem;		//определение типа значений элементов массива
typedef telem tmas[RAZ];	//определение типа массива

void inputmas(tmas, int);
void outputmas(tmas, int);
void sortirovka_massiva(tmas, int);
int opredel_num_unical_elems(tmas, int);
telem* sozd_arr_unical_elems(tmas, int, int);

int main() {
    setlocale(LC_ALL, "Russian");
    tmas arr; // массив

    cout << "Введите массив из " << RAZ << " элементов.\n";
    inputmas(arr, RAZ);
    cout << "Введенный массив из " << RAZ << " элементов.\n";
    outputmas(arr, RAZ);

    sortirovka_massiva(arr, RAZ);
    cout << "Результат сортировки массива из " << RAZ << " элементов.\n";
    outputmas(arr, RAZ);

    int num_unical = opredel_num_unical_elems(arr, RAZ);
    cout << "Количество уникальных элементов в массиве = " << num_unical << endl;

    telem* unical_elems = sozd_arr_unical_elems(arr, RAZ, num_unical);
    cout << "Результат формирования массива уникальных элементов.\n";
    outputmas(unical_elems, num_unical);
    delete[] unical_elems;

    return 0;
}

void inputmas(tmas arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }
}

void outputmas(tmas arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
}

void sortirovka_massiva(tmas arr, int size) {
    if (size == 0) {
        return;
    }
    tmas sort_arr;
    for (int i = 0; i < size; i++) {
        int count_elems_is_more = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] > arr[j] || (arr[i] == arr[j] && j < i)) {
                ++count_elems_is_more;
            }
        }
        sort_arr[count_elems_is_more] = arr[i];
    }
    for (int i = 0; i < size; i++) {
        arr[i] = sort_arr[i];
    }
}

int opredel_num_unical_elems(tmas arr, int size) {
    if (size == 1) {
        return 1;
    }
    int num_unical = size;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                num_unical--;
                break;
            }
        }
    }
    return num_unical;
}

telem* sozd_arr_unical_elems(tmas arr, int size, int num_unical) {
    telem* unical_elems = new telem[num_unical];
    int count_pos_uniq = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            unical_elems[count_pos_uniq++] = arr[i];
        }
    }
    // добавляем последний элемент если он является уникальным
    if (arr[size - 1] != arr[size - 2]) {
        unical_elems[count_pos_uniq] = arr[size - 1];
    }
    return unical_elems;
}
