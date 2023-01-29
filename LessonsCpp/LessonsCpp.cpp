#include <iostream>
#include <vector>

using namespace std;

int Sum(int& a, int& b) {
    a += 7;
    cout << "&a_foo = " << &a << endl;
    cout << "&b_foo = " << &b << endl;
    return a + b;
}

void Sort(vector<int>& elements) {
    for (int& value : elements) {
        value *= (-1);
    }
}

void Print(const vector<int>& elements) {
    for (const int& value : elements) {
        cout << value << ' ';
    }
    cout << endl;
}

int main() {
    vector<int> test = { 2,6,-7,2,6,-2,0 };
    cout << "before" << endl;
    Print(test);
    Sort(test);
    cout << "after" << endl;
    Print(test);
    return 0;
}