#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

/// ЛР02. Линейные и циклические списка. Вариант 11

struct LinearList {
    int coeff;
    LinearList* next;
    LinearList* prev;
};

void AddListElem(LinearList*& node, int new_list_elem) {
    LinearList* new_elem = new LinearList;
    new_elem->next = nullptr;
    new_elem->prev = nullptr;
    new_elem->coeff = new_list_elem;
    if (node == nullptr) {
        node = new_elem;
    } else {
        LinearList* tmp = node;
        new_elem->prev = tmp;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            new_elem->prev = tmp;
        }
        tmp->next = new_elem;
    }
}

// Освобождение памяти, выделенной для элементов списка
void ClearList(LinearList*& node) {
    if (node == nullptr) {
        return;
    }
    while (node->next != nullptr) {
        LinearList* tmp = node->next;
        delete[] node;
        node = tmp;
    }
    delete node;
    node = nullptr;
}

// Вывод последовательности в прямом направлении, начиная с node
void PrintForwardSequence(const LinearList* node, ostream& out = cout) {
    if (node == nullptr) {
        out << "There isn't forward sequence.\n"s;
        return;
    }
    while (node->next != nullptr) {
        out << node->coeff << ' ';
        node = node->next;
    }
    out << node->coeff << '\n';
}

// Вывод последовательности в обратном направлении, начиная с node
void PrintReverseSequence(const LinearList* node, ostream& out = cout) {
    if (node == nullptr) {
        out << "There isn't reverse sequence.\n"s;
        return;
    }
    while (node->prev != nullptr) {
        out << node->coeff << ' ';
        node = node->prev;
    }
    out << node->coeff << '\n';
}

// ОСНОВНАЯ ФУНКЦИЯ
void FindTwoSequences(LinearList*& list, int pivot_element, ostream& out = cout) {
    if (list == nullptr) {
        out << "List is empty.\n"s;
        return;
    }
    const LinearList* pos_pivot_element = list;
    while (pos_pivot_element->coeff != pivot_element && pos_pivot_element->next != nullptr) {
        pos_pivot_element = pos_pivot_element->next;
    }
    if (pos_pivot_element->coeff != pivot_element) {
        out << pivot_element << " there isn't at list.\n"s;
        return;
    }
    if (pos_pivot_element->next == nullptr && pos_pivot_element->prev == nullptr) {
        out << "The list contains only one item.\n"s;
        return;
    }

    const LinearList* reverse = pos_pivot_element->prev;
    const LinearList* forward = pos_pivot_element->next;

    // вывод первой
    out << "Reverse sequence: "s;
    PrintReverseSequence(reverse, out);

    // вывод второй
    out << "Forward sequence: "s;
    PrintForwardSequence(forward, out);
}

// =========================== НАЧАЛО ТЕСТОВ, ПРОВЕРЯЮЩИХ КОРРЕКТНОСТЬ РАБОТЫ ===========================>
// Когда список пустой
void TestEmptyList() {
    LinearList* list = nullptr;
    ostringstream out;
    string expected_print = "List is empty.\n"s;
    FindTwoSequences(list, 5, out);
    assert(out.str() == expected_print);
    ClearList(list);
    cerr << "TestEmptyList has passed\n"s;
}

// Когда искомого числа нет в списке
void TestAbsenceNumberInSequence() {
    LinearList* list = nullptr;
    ostringstream out;
    constexpr int kFindNumber = 7; // любое нечетное число
    string expected_print = to_string(kFindNumber) + " there isn't at list.\n"s;
    for (int i = 0; i < 15; i += 2) {
        AddListElem(list, i);
    }
    FindTwoSequences(list, kFindNumber, out);
    assert(out.str() == expected_print);
    ClearList(list);
    cerr << "TestAbsenceNumberInSequence has passed\n"s;
}

// Когда список состоит из одного элемента
void TestListWithOneElement() {
    LinearList* list = nullptr;
    ostringstream out;
    constexpr int kFindNumber = 42; // любое число
    string expected_print = "The list contains only one item.\n"s;
    AddListElem(list, kFindNumber);
    FindTwoSequences(list, kFindNumber, out);
    assert(out.str() == expected_print);
    ClearList(list);
    cerr << "TestListWithOneElement has passed\n"s;
}

// Существует только обратная последовательность
void TestOnlyReverseSequence() {
    LinearList* list = nullptr;
    ostringstream out;
    for (int i = 0; i < 10; ++i) {
        AddListElem(list, i);
    }
    FindTwoSequences(list, 9, out);
    ostringstream expected_out {
        "Reverse sequence: 8 7 6 5 4 3 2 1 0\n"s
        "Forward sequence: There isn't forward sequence.\n"s
    };
    assert(out.str() == expected_out.str());
    ClearList(list);
    cerr << "TestOnlyReverseSequence has passed\n"s;
}

// Существует только прямая последовательность
void TestOnlyForwardSequence() {
    LinearList* list = nullptr;
    ostringstream out;
    for (int i = 0; i < 10; ++i) {
        AddListElem(list, i);
    }
    FindTwoSequences(list, 0, out);
    ostringstream expected_out {
        "Reverse sequence: There isn't reverse sequence.\n"s
        "Forward sequence: 1 2 3 4 5 6 7 8 9\n"s
    };
    assert(out.str() == expected_out.str());
    ClearList(list);
    cerr << "TestOnlyForwardSequence has passed\n"s;
}

// Обе последовательности существуют
void TestThereIsTwoSequences() {
    LinearList* list = nullptr;
    ostringstream out;
    for (int i = 0; i < 10; ++i) {
        AddListElem(list, i);
    }
    FindTwoSequences(list, 5, out);
    ostringstream expected_out {
        "Reverse sequence: 4 3 2 1 0\n"s
        "Forward sequence: 6 7 8 9\n"s
    };
    assert(out.str() == expected_out.str());
    ClearList(list);
    cerr << "TestThereIsTwoSequences has passed\n"s;
}

void RunAllTests() {
    TestEmptyList();
    TestAbsenceNumberInSequence();
    TestListWithOneElement();
    TestOnlyReverseSequence();
    TestOnlyForwardSequence();
    TestThereIsTwoSequences();
    cerr << ">>> AllTests has passed <<<\n"s;
    cerr << "===========================\n"s;
}

// <=========================== КОНЕЦ ТЕСТОВ, ПРОВЕРЯЮЩИХ КОРРЕКТНОСТЬ РАБОТЫ ===========================

void Example() {
    static int count = 1;
    cout << "Run example "s << count++ << "...\n"s;
    cout << "Enter size list: "s;
    int size = 0;
    cin >> size;
    LinearList* list = nullptr;
    for (int i = 0; i < size; ++i) {
        cout << "List["s << i << "] = "s;
        int value = 0;
        cin >> value;
        AddListElem(list, value);
    }
    cout << "List elements:\n"s;
    PrintForwardSequence(list);

    cout << "Enter find element: "s;
    int find_element = 0;
    cin >> find_element;
    FindTwoSequences(list, find_element);
    ClearList(list);
}

int main() {
    RunAllTests();
    char answer = 'y';
    while (answer == 'y') {
        Example();
        cout << "Do run example again? [y/n]\n"s;
        cin >> answer;
    }
    return 0;
}
