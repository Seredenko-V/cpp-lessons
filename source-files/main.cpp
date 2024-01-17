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

// для тестов
#include <cassert>
#include <string>

using namespace std;

const int RAZ = 10;		//предельный размер массива
typedef int telem;		//определение типа значений элементов массива
typedef telem tmas[RAZ];	//определение типа массива

void inputmas(tmas, int);
void outputmas(tmas, int);
int opredel_num_unical_elems(tmas, int);
bool sushestvuet_element(telem*, int, int);
telem* sozd_arr_unical_elems(tmas, int, int);

/// ============================= НАЧАЛО ТЕСТОВ ==============================

void AssertEqualArr(telem* lhs, int lhs_size, telem* rhs, int rhs_size) {
    assert(lhs_size == rhs_size);
    for (int i = 0; i < lhs_size; ++i) {
        assert(lhs[i] == rhs[i]);
    }
}

void TestDetermNumUnique() {
    {
        constexpr uint16_t kSize = 12u;
        telem arr[kSize]{1,8,2,4,8,1,7,8,7,2,5,2};
        assert(opredel_num_unical_elems(arr, kSize) == 6);
    }{
        constexpr uint16_t kSize = 5u;
        telem arr[kSize]{5,5,5,5,5};
        assert(opredel_num_unical_elems(arr, kSize) == 1);
    }{
        constexpr uint16_t kSize = 10u;
        telem arr[kSize]{1,9,7,254,532,72,-121,-331,6367,99};
        assert(opredel_num_unical_elems(arr, kSize) == kSize);
    }
    cerr << "TestDetermNumUnique passed\n"s;
}

void TestCreateArrUniqueElems() {
    {
        constexpr uint16_t kSize = 12u;
        telem arr[kSize]{1,8,2,4,8,1,7,8,7,2,5,2};
        constexpr uint16_t kSizeExpected = 6u;
        telem expected[kSizeExpected]{1,8,2,4,7,5};
        telem* reuslt_arr = sozd_arr_unical_elems(arr, kSize, kSizeExpected);
        AssertEqualArr(reuslt_arr, kSizeExpected, expected, kSizeExpected);
        delete[] reuslt_arr;
    }{
        constexpr uint16_t kSize = 10u;
        telem arr[kSize]{1,1,1,1,1,1,1,1,1,1};
        constexpr uint16_t kSizeExpected = 1u;
        telem expected[kSizeExpected]{1};
        telem* reuslt_arr = sozd_arr_unical_elems(arr, kSize, kSizeExpected);
        AssertEqualArr(reuslt_arr, kSizeExpected, expected, kSizeExpected);
        delete[] reuslt_arr;
    }{
        constexpr uint16_t kSize = 10u;
        telem arr[kSize]{1,9,7,254,532,72,-121,-331,6367,99};
        constexpr uint16_t kSizeExpected = kSize;
        telem expected[kSizeExpected]{1,9,7,254,532,72,-121,-331,6367,99};
        telem* reuslt_arr = sozd_arr_unical_elems(arr, kSize, kSizeExpected);
        AssertEqualArr(reuslt_arr, kSizeExpected, expected, kSizeExpected);
        delete[] reuslt_arr;
    }
    cerr << "TestCreateArrUniqueElems passed\n"s;
}

void RunAllTests() {
    TestDetermNumUnique();
    TestCreateArrUniqueElems();
    cerr << ">>> AllTests passed <<<\n"s;
}

/// ============================= КОНЕЦ ТЕСТОВ ===============================

int main() {
    setlocale(LC_ALL, "Russian");
    RunAllTests();

    tmas arr; // массив

    cout << "Введите массив из " << RAZ << " элементов.\n";
    inputmas(arr, RAZ);
    cout << "Введенный массив из " << RAZ << " элементов.\n";
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

bool sushestvuet_element(telem* arr, int size, int element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return true;
        }
    }
    return false;
}

telem* sozd_arr_unical_elems(tmas arr, int size, int num_unical) {
    if (size == 0) {
        return nullptr;
    }

    telem* unical_elems = new telem[num_unical];
    unical_elems[0] = arr[0];
    int count_pos_uniq = 1;

    for (int i = 1; i < size; i++) {
        if (!sushestvuet_element(unical_elems, size, arr[i])) {
            unical_elems[count_pos_uniq++] = arr[i];
        }
    }
    return unical_elems;
}
