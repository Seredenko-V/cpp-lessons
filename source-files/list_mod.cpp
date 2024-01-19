#include "list_mod.h"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

void AddElemToEndList(List*& list, telem new_element) {
    List* new_node = new List;
    new_node->data = new_element;
    if (list == nullptr) {
        list = new_node;
    } else {
        List* tmp = list;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
}

void ClearList(List*& list) {
    if (list == nullptr) {
        return;
    }
    while (list->next != nullptr) {
        List* next = list->next;
        delete list;
        list = next;
    }
    delete list;
    list = nullptr;
}

// Вывод последовательности в прямом направлении, начиная с node
void PrintList(const List* list, ostream& out = cout) {
    if (list == nullptr) {
        out << "There isn't forward sequence.\n"s;
        return;
    }
    while (list->next != nullptr) {
        out << list->data << ' ';
        list = list->next;
    }
    out << list->data << '\n';
}

List* FindLastNegativeElem(List*& list) {
    if (list == nullptr) {
        return nullptr;
    }
    List* last_negative = list;
    List* counter = list->next;
    while (counter != nullptr) {
        if (counter->data < 0) {
            last_negative = counter;
        }
        counter = counter->next;
    }
    return last_negative;
}

void SetLastNegativeElemToHead(List*& list) {
    if (list == nullptr) {
        return;
    }
    List* last_negative = list;
    List* before_last_nagative = nullptr;
    List* counter = list;
    while (counter->next != nullptr) {
        if (counter->next->data < 0) {
            before_last_nagative = counter;
            last_negative = counter->next;
        }
        counter = counter->next;
    }
    // если был найден хотя бы один отрицательный элемент
    if (before_last_nagative != nullptr) {
        before_last_nagative->next = last_negative->next;
        last_negative->next = list;
        list = last_negative;
    }
}


namespace tests {
    void TestCreateAndClearList() {
        constexpr uint16_t kListSize = 10u;
        List* list = nullptr;

        for (uint16_t i = 0; i < kListSize; ++i) {
            AddElemToEndList(list, i);
            List* counter = list;
            while (counter != nullptr && counter->next != nullptr) {
                counter = counter->next;
            }
            assert(counter->data == i);
        }
        ClearList(list);
        assert(list == nullptr);
        cerr << "TestCreateAndClearList passed.\n"s;
    }

    List* CreateList(const vector<int>& elems) {
        List* list = nullptr;
        for (int element : elems) {
            AddElemToEndList(list, element);
        }
        return list;
    }

    vector<int> GetListContent(const List* list) {
        vector<int> content;
        if (list == nullptr) {
            return content;
        }
        while (list != nullptr) {
            content.push_back(list->data);
            list = list->next;
        }
        return content;
    }

    void TestSetLastNegativeElemToHead() {
        {
            vector<int> elems{2,5,7,2,-4,1,5,-6,2};
            vector<int> expected{-6,2,5,7,2,-4,1,5,2};
            List* list = CreateList(elems);
            SetLastNegativeElemToHead(list);
            vector<int> result_content = GetListContent(list);
            assert(result_content == expected);
            ClearList(list);
        }{
            vector<int> elems{2,5,7,2,-4,1,5,-6,-2};
            vector<int> expected{-2,2,5,7,2,-4,1,5,-6};
            List* list = CreateList(elems);
            SetLastNegativeElemToHead(list);
            vector<int> result_content = GetListContent(list);
            assert(result_content == expected);
            ClearList(list);
        }{
            vector<int> elems{2,5,7,2,4,1,5,6,2};
            List* list = CreateList(elems);
            SetLastNegativeElemToHead(list);
            vector<int> result_content = GetListContent(list);
            assert(result_content == elems);
            ClearList(list);
        }
        cerr << "TestSetLastNegativeElemToHead passed.\n"s;
    }

    void RunAllTests() {
        TestCreateAndClearList();
        TestSetLastNegativeElemToHead();
        cerr << ">>> AllTests passed <<<\n"s;
    }
} // namespace tests
