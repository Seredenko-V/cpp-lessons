/// ЛР09-А. Динамические массивы. Вариант 36.
/// Задача:
/// Дан массив z0, z1, z2,…, zn-1. Определить произведение суммы положительных значений элементов массива,
/// лежащих между первым элементом с наибольшим неположительным значением и последним элементом массива
/// с отрицательным значением, на их количество.

#include <clocale>
#include <iostream>
#include <cassert>

using namespace std;

typedef int telem; // объявление типа элемента массива
typedef telem* tarr; // объявление типа "указатель на telem"

tarr CreateArray() {
    cout << "Введите размер массива:\n";
    int size = 0;
    cin >> size;
    tarr arr = new telem[size];
    cout << "Введите элементы массива\n";
    for (int i = 0; i < size; ++i) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }
    return arr;
}

int FindPosFirstBigNegativeElement(tarr arr, int size) {
    int pos_global_min = 0;
    telem global_min = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < global_min) {
            global_min = arr[i];
            pos_global_min = i;
        }
    }
    return pos_global_min;
}

int FindPosLastNegativeElement(tarr arr, int size) {
    int pos_last_negative = size - 1;
    for (int i = pos_last_negative; i >= 0; --i) {
        if (arr[i] < 0) {
            pos_last_negative = i;
            break;
        }
    }
    return pos_last_negative;
}

telem Calculate(tarr arr, int from_pos, int to_pos) {
    if (to_pos < from_pos) {
        return 0;
    }
    telem result = 0;
    for (int i = from_pos + 1; i < to_pos; ++i) {
        result += arr[i];
    }
    return result * (to_pos - from_pos - 1);
}


namespace tests {
    void TestFindFirstBigNegativeElement() {
        {
            constexpr uint32_t kSize = 5u;
            tarr arr = new telem[kSize]{-5,5,2,8,-1};
            assert(FindPosFirstBigNegativeElement(arr, kSize) == 0);
            delete[] arr;
        }{
            constexpr uint32_t kSize = 10u;
            tarr arr = new telem[kSize]{-5,35,42,8,-1,7,-25,9,12,44};
            assert(FindPosFirstBigNegativeElement(arr, kSize) == 6);
            delete[] arr;
        }{
            constexpr uint32_t kSize = 10u;
            tarr arr = new telem[kSize]{-5,35,42,8,-1,7,-25,9,12,-44};
            assert(FindPosFirstBigNegativeElement(arr, kSize) == 9);
            delete[] arr;
        }
        cerr << "TestFindFirstBigNegativeElement passed\n"s;
    }

    void TestFindPosLastNegativeElement() {
        {
            constexpr uint32_t kSize = 5u;
            tarr arr = new telem[kSize]{-5,5,2,8,-1};
            assert(FindPosLastNegativeElement(arr, kSize) == 4);
            delete[] arr;
        }{
            constexpr uint32_t kSize = 10u;
            tarr arr = new telem[kSize]{-5,35,42,8,-1,7,-25,9,12,44};
            assert(FindPosLastNegativeElement(arr, kSize) == 6);
            delete[] arr;
        }{
            constexpr uint32_t kSize = 10u;
            tarr arr = new telem[kSize]{-5,35,42,8,-1,7,25,9,12,44};
            assert(FindPosLastNegativeElement(arr, kSize) == 4);
            delete[] arr;
        }{
            constexpr uint32_t kSize = 10u;
            tarr arr = new telem[kSize]{2,-5,6,-35, 9,1,10,30,-20, -8};
            assert(FindPosLastNegativeElement(arr, kSize) == 9);
            delete[] arr;
        }
        cerr << "TestFindPosLastNegativeElement passed\n"s;
    }

    void TestCalculate() {
        {
            constexpr uint32_t kSize = 5u;
            tarr arr = new telem[kSize]{-5, 5,2,8, -1};
            assert(Calculate(arr, FindPosFirstBigNegativeElement(arr, kSize), FindPosLastNegativeElement(arr, kSize)) == 45); // (5+2+8) * 3
            delete[] arr;
        }{
            constexpr uint32_t kSize = 10u;
            tarr arr = new telem[kSize]{2,-5,6,-35, 9,1,10,30,-20, -8};
            assert(Calculate(arr, FindPosFirstBigNegativeElement(arr, kSize), FindPosLastNegativeElement(arr, kSize)) == 150); // 30 * 5
            delete[] arr;
        }
        cerr << "TestCalculate passed\n"s;
    }

    void RunAllTests() {
        TestFindFirstBigNegativeElement();
        TestFindPosLastNegativeElement();
        TestCalculate();
        cerr << ">>> AllTests passed <<<\n"s;
    }
} // namespace tests


int main() {
    setlocale(LC_ALL, "Russian");
    tests::RunAllTests();
    return 0;
}
