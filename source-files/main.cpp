#include <iostream>
#include <cassert>

using namespace std;

/// ЛР05. Алгоритмы сортировки. Вариант 11.
/// Задача: Найти количество повторяющихся чисел среди элементов массива
/// Алгоритм сортировки: Подсчетом

template <typename Type>
void PrintArray(Type arr[], uint32_t arr_size, ostream& out = cout) {
    if (arr_size == 0) {
        return;
    }
    assert(arr != nullptr);
    out << '[';
    for (uint32_t i = 0; i < arr_size - 1; ++i) {
        out << arr[i] << ',';
    }
    out << arr[arr_size - 1] << "]\n";
}

/// Сложность: O(N^2) по времени - вложенный цикл и O(N) по памяти - доп. массив
template <typename Type>
Type* SortCounting(Type arr[], uint32_t arr_size) {
    if (arr_size == 0) {
        return nullptr;
    }
    assert(arr != nullptr);
    Type* sort_arr = new Type[arr_size];
    for (uint32_t i = 0; i < arr_size; ++i) {
        uint32_t count_elems_is_more = 0;
        for (uint32_t j = 0; j < arr_size; ++j) {
            if (arr[i] > arr[j] || (arr[i] == arr[j] && j < i)) {
                ++count_elems_is_more;
            }
        }
        sort_arr[count_elems_is_more] = arr[i];
    }
    return sort_arr;
}

/// Сложность: O(N) по времени и O(1) по памяти
template <typename Type>
uint32_t FindNumSameElements(Type arr[], uint32_t arr_size) {
    if (arr_size < 2) {
        return 0;
    }
    assert(arr != nullptr);
    uint32_t num_same_elements = 0;
    bool is_continue_same = false;
    for (uint32_t i = 0; i < arr_size - 1; ++i) {
        if (arr[i] == arr[i + 1] && !is_continue_same) {
            is_continue_same = true;
            ++num_same_elements;
        } else if (arr[i] != arr[i + 1]) {
            is_continue_same = false;
        }
    }
    return num_same_elements;
}

namespace tests {
    // Работает для всех типов данных, имеющих operator!=, кроме double из-за точности
    template <typename Type>
    bool ArraysIsSame(Type lhs_arr[], uint32_t lhs_size, Type rhs_arr[], uint32_t rhs_size) {
        if (lhs_size != rhs_size) {
            return false;
        }
        for (uint32_t i = 0; i < lhs_size; ++i) {
            if (lhs_arr[i] != rhs_arr[i]) {
                return false;
            }
        }
        return true;
    }

    void TestSort() {
        {
            constexpr uint32_t kSize = 7;
            int arr[kSize]{7,6,5,4,3,2,1};
            int expected_arr[kSize]{1,2,3,4,5,6,7};
            int* sort_arr = SortCounting(arr, kSize);
            assert(ArraysIsSame(sort_arr, kSize, expected_arr, kSize));
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 5;
            int arr[kSize]{4,123,4,5,4};
            int expected_arr[kSize]{4,4,4,5,123};
            int* sort_arr = SortCounting(arr, kSize);
            assert(ArraysIsSame(sort_arr, kSize, expected_arr, kSize));
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 3;
            int arr[kSize]{1,1,1};
            int expected_arr[kSize]{1,1,1};
            int* sort_arr = SortCounting(arr, kSize);
            assert(ArraysIsSame(sort_arr, kSize, expected_arr, kSize));
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 6;
            int arr[kSize]{1,1,5,1,1,1};
            int expected_arr[kSize]{1,1,1,1,1,5};
            int* sort_arr = SortCounting(arr, kSize);
            assert(ArraysIsSame(sort_arr, kSize, expected_arr, kSize));
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 6;
            int arr[kSize]{-1,1,5,1,-1,-45};
            int expected_arr[kSize]{-45,-1,-1,1,1,5};
            int* sort_arr = SortCounting(arr, kSize);
            assert(ArraysIsSame(sort_arr, kSize, expected_arr, kSize));
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 0;
            int arr[kSize];
            int* sort_arr = SortCounting(arr, kSize);
            assert(sort_arr == nullptr);
        }{
            constexpr uint32_t kSize = 6;
            int arr[kSize]{2,2,2,2,4,5};
            int expected_arr[kSize]{2,2,2,2,4,5};
            int* sort_arr = SortCounting(arr, kSize);
            assert(ArraysIsSame(sort_arr, kSize, expected_arr, kSize));
            delete[] sort_arr;
        }
        cerr << "TestSortInt has passed\n";
    }

    void TestFindNumSameElements() {
        {
            constexpr uint32_t kSize = 7;
            int arr[kSize]{7,6,5,4,3,2,1};
            int* sort_arr = SortCounting(arr, kSize);
            assert(FindNumSameElements(sort_arr, kSize) == 0);
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 3;
            int arr[kSize]{7,7,7};
            int* sort_arr = SortCounting(arr, kSize);
            assert(FindNumSameElements(sort_arr, kSize) == 1);
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 8;
            int arr[kSize]{7,7,7,2,1,4,2,1};
            int* sort_arr = SortCounting(arr, kSize);
            assert(FindNumSameElements(sort_arr, kSize) == 3); // 1,2,7
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 0;
            int arr[kSize];
            int* sort_arr = SortCounting(arr, kSize); // nullptr
            assert(FindNumSameElements(sort_arr, kSize) == 0);
        }{
            constexpr uint32_t kSize = 1;
            int arr[kSize]{9};
            int* sort_arr = SortCounting(arr, kSize);
            assert(FindNumSameElements(sort_arr, kSize) == 0);
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 6;
            int arr[kSize]{-1,1,5,1,-1,-45};
            int* sort_arr = SortCounting(arr, kSize);
            assert(FindNumSameElements(sort_arr, kSize) == 2); // -1,1
            delete[] sort_arr;
        }{
            constexpr uint32_t kSize = 6;
            int arr[kSize]{2,2,2,2,4,5};
            int* sort_arr = SortCounting(arr, kSize);
            assert(FindNumSameElements(sort_arr, kSize) == 1); // 2
            delete[] sort_arr;
        }
        cerr << "TestFindNumSameElements has passed\n";
    }

    void RunAllTests() {
        TestSort();
        TestFindNumSameElements();
        cerr << ">>> AllTest has passed <<<\n";
    }
} // namespace tests

void RunExpample() {
    static uint32_t count = 1u;
    cout << "Run example "s << count++ << "...\n"s;
    cout << "Enter size array: "s;
    int size = 0;
    cin >> size;
    if (size < 0) {
        cout << "Entered negative size array.\n"s;
        return;
    }
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        cout << "arr["s << i << "] = "s;
        cin >> arr[i];
    }
    cout << "Array elements:\n"s;
    PrintArray(arr, size);
    int* sort_arr = SortCounting(arr, size);
    cout << "Sort array:\n"s;
    PrintArray(sort_arr, size);
    cout << "Number same elements = "s << FindNumSameElements(sort_arr, size) << endl;
    delete[] arr;
    delete[] sort_arr;
}

int main() {
    tests::RunAllTests();
    char answer = 'y';
    while (answer == 'y') {
        RunExpample();
        cout << "Do run example again? [y/n]\n"s;
        cin >> answer;
    }
    return 0;
}
