/// ЛР14. Линейные списки. Вариант 36.
/// Задача:
/// Перенести в начало списка его последний отрицательный элемент.

#include "list_mod.h"

#include <locale.h>
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int size_list = 0;
    cout << "Введите количество элементов списка: ";
    cin >> size_list;

    List* list = nullptr;
    cout << "Введите элементы списка\n";
    for (int i = 0; i < size_list; i++) {
        cout << "list[" << i << "] = ";
        telem element;
        cin >> element;
        add_elem_to_end_list(list, element);
    }

    set_Last_negative_elem_to_head(list);
    cout << "Результат переноса в начало списка его последнего отрицательного элемента:\n";
    print_list(list);
    clear_list(list);
    return 0;
}
