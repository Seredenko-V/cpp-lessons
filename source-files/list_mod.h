#pragma once

typedef int telem;

struct List {
    telem data{};
    List* next = nullptr;
};

void AddElemToEndList(List*& list, telem new_element);
void ClearList(List*& list);

// если отрицательных элементов нет - изменений не происходит
void SetLastNegativeElemToHead(List*& list);

namespace tests {
    void TestCreateAndClearList();
    void TestSetLastNegativeElemToHead();
    void RunAllTests();
} // namespace tests
