#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void Sort(vector<int>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        for (size_t j = i + 1; j < elements.size(); ++j) {
            if (elements[j] < elements[i]) {
                int tmp = elements[i];
                elements[i] = elements[j];
                elements[j] = tmp;
            }
        }
    }
}

void Tests() {
    {
        vector<int> values = { -2,5,3,0 };
        vector<int> etalon = { -2,0,3,5 };
        Sort(values);
        assert(values == etalon);
    }
    {
        vector<int> values = { -2,-5,-3,0 };
        vector<int> etalon = { -5,-3,-2,0 };
        Sort(values);
        assert(values == etalon);
    }
    {
        vector<int> values = { 5,5,5,5,5,5 };
        vector<int> etalon = { 5,5,5,5,5,5 };
        Sort(values);
        assert(values == etalon);
    }
    {
        vector<int> values;
        Sort(values);
        assert(values.empty());
    }
    {
        vector<int> values = { 5,0,0,0,0,3,3,3,3,1 };
        vector<int> etalon = { 0,0,0,0,1,3,3,3,3,5 };
        Sort(values);
        assert(values == etalon);
    }

    cout << "All tests passed"s << endl;
}

int main() {
    Tests();
    return 0;
}