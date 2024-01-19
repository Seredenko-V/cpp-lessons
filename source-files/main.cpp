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

tarr create_array(int size) {
    tarr arr = new telem[size];
    cout << "Введите элементы массива\n";
    for (int i = 0; i < size; ++i) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }
    return arr;
}

int find_pos_first_big_negative_element(tarr arr, int size) {
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

int find_pos_last_negative_element(tarr arr, int size) {
    int pos_last_negative = size - 1;
    for (int i = pos_last_negative; i >= 0; --i) {
        if (arr[i] < 0) {
            pos_last_negative = i;
            break;
        }
    }
    return pos_last_negative;
}

telem calculate(tarr arr, int from_pos, int to_pos) {
    if (to_pos < from_pos) {
        return 0;
    }
    telem result = 0;
    for (int i = from_pos + 1; i < to_pos; ++i) {
        result += arr[i];
    }
    return result * (to_pos - from_pos - 1);
}


int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите размер массива:\n";
    int size = 0;
    cin >> size;
    tarr arr = create_array(size);

    int from_pos = find_pos_first_big_negative_element(arr, size);
    int to_pos = find_pos_last_negative_element(arr, size);

    cout << "Вычисления:\n(";
    bool is_first = true;
    for (int i = from_pos + 1; i < to_pos; ++i) {
        if (!is_first) {
            cout << '+';
        }
        cout << arr[i];
        is_first = false;
    }
    telem result = calculate(arr, from_pos, to_pos);
    cout << ") * 3 = " << result << endl;
    delete[] arr;
    return 0;
}
