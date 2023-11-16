#include <iostream>
#include <string>

using namespace std;

/// ЛР02. Линейные и циклические списка. Вариант 11

struct LinearList {
    int coeff;
    LinearList* next;
    LinearList* prev;
};

// по значению т.к. указатель - легкий объект
ostream& operator<<(ostream& out, LinearList* list) {
    while (list->next != nullptr) {
        out << list->coeff << ' ';
        list = list->next;
    }
    out << list->coeff;
    return out;
}

void AddListElem(LinearList*& first, int new_list_elem) {
    LinearList* new_elem = new LinearList;
    new_elem->next = nullptr;
    new_elem->prev = nullptr;
    new_elem->coeff = new_list_elem;
    if (first == nullptr) {
        first = new_elem;
    } else {
        LinearList* tmp = first;
        new_elem->prev = tmp;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            new_elem->prev = tmp;
        }
        tmp->next = new_elem;
    }
}

void FindTwoSequences(LinearList*& list, int pivot_element) {
    if (list == nullptr) {
        cerr << "List is empty.\n"s;
        return;
    }
    const LinearList* pos_pivot_element = list;
    while (pos_pivot_element->coeff != pivot_element && pos_pivot_element->next != nullptr) {
        pos_pivot_element = pos_pivot_element->next;
    }
    if (pos_pivot_element->coeff != pivot_element) {
        cerr << pivot_element << " there isn't at list.\n"s;
        return;
    }

    const LinearList* reverse = pos_pivot_element->prev;
    const LinearList* forward = pos_pivot_element->next;

    // вывод первой
    cout << "Reverse sequence: "s;
    while (reverse->prev != nullptr) {
        cout << reverse->coeff << ' ';
        reverse = reverse->prev;
    }
    cout << reverse->coeff << '\n';


    // вывод второй
    cout << "Forward sequence: "s;
    while (forward->next != nullptr) {
        cout << forward->coeff << ' ';
        forward = forward->next;
    }
    cout << forward->coeff << '\n';
}


int main() {
    LinearList* first = nullptr;
    for (int i = 0; i < 15; i += 2) {
        AddListElem(first, i);
    }
    cout << "List elements:\n"s;
    cout << first << endl << endl;
    FindTwoSequences(first, 5);
    return 0;
}
