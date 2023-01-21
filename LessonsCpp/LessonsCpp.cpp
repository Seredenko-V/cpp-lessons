#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

vector<vector<int>> ParseValue(const vector<int>& elements) {
    vector<vector<int>> result;
    if (elements.empty()) {
        return result;
    }
    vector<int> box;

    for (size_t i = 0; i < elements.size() - 1; ++i) {
        box.push_back(elements[i]);
        if (elements[i + 1] != elements[i]) {
            result.push_back(box);
            box.clear();
        }
    }
    box.push_back(elements.back());
    result.push_back(box);
    return result;
}

void Test()
{
    {
        vector<int> elements = { 8,8,8,1,1,1,3 };
        vector<vector<int>> etalon = { {8,8,8}, {1,1,1}, {3} };
        assert(ParseValue(elements) == etalon);
    }
    {
        vector<int> elements = { 8,1,3 };
        vector<vector<int>> etalon = { {8}, {1}, {3} };
        assert(ParseValue(elements) == etalon);
    }
    {
        vector<int> elements = { 8,1,1,1,3,6,3,6,8,8 };
        vector<vector<int>> etalon = { {8}, {1,1,1}, {3}, {6}, {3}, {6}, {8,8} };
        assert(ParseValue(elements) == etalon);
    }
    {
        vector<int> elements = { 5 };
        vector<vector<int>> etalon = { {5} };
        assert(ParseValue(elements) == etalon);
    }
    {
        vector<int> elements;
        assert(ParseValue(elements).empty());
    }   
}

int main() {
    Test();
    return 0;
}
