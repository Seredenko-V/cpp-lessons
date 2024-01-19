#pragma once

typedef int telem;

struct List {
    telem data{};
    List* next = nullptr;
};

void add_elem_to_end_list(List*& list, telem new_element);
void clear_list(List*& list);

// если отрицательных элементов нет - изменений не происходит
void set_Last_negative_elem_to_head(List*& list);

void print_list(const List* list);
