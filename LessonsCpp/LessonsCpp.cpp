#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

vector<int> operator+(const vector<int>& first, const vector<int>& second) {
    if (first.size() != second.size()) {
        throw logic_error("size1 != size2"s);
    }
    vector<int> result(first.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = first[i] + second[i];
    }
    return result;
}

ostream& operator<<(ostream& out, const vector<int>& second) {
    for (const int& value : second) {
        cout << value << ' ';
    }
    return out;
}

vector<int>& operator++(vector<int>& first) {
    for (size_t i = 0; i < first.size(); ++i) {
        first[i]++;
    }
    return first;
}

vector<int> operator++(vector<int>& first, int fix) {
    vector<int> tmp = first;
    for (size_t i = 0; i < first.size(); ++i) {
        first[i]++;
    }
    return tmp;
}

int main() {
    vector<int> a{ 1,2,3,4,5 };
    vector<int> b{ 9,8,7,6,5 };
    try {
        vector<int> c = a + b;
        cout << c << endl;
        vector<int> d = c++ + a;
        cout << d << endl;
    } catch (const logic_error& except) {
        cout << except.what() << endl;
    }
    return 0;
}
