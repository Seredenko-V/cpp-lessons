#include "list_mod.h"

#include <iostream>

using namespace std;

void add_elem_to_end_list(List*& list, telem new_element) {
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

void clear_list(List*& list) {
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
void print_list(const List* list) {
    if (list == nullptr) {
        cout << "There isn't forward sequence.\n"s;
        return;
    }
    while (list->next != nullptr) {
        cout << list->data << ' ';
        list = list->next;
    }
    cout << list->data << '\n';
}

void set_Last_negative_elem_to_head(List*& list) {
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
