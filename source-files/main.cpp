#include <iostream>
#include <string>

using namespace std;

int main() {
    int value = 5;
    cout << "value before change = "s << value << endl;
    int* ptr_value = &value;
    cout << "*ptr_value = "s << *ptr_value << endl;
    *ptr_value = 9;
    cout << "value after change = "s << value << endl;

    return 0;
}
