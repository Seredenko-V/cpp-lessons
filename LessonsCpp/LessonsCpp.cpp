#include <iostream>

using namespace std;

int main() {
    int a = 4;
    cout << "a = " << a << endl;
    cout << "&a = " << &a << endl;

    // ==================== указатель ===================
    cout << "==================== указатель ===================" << endl;
    int* ptr_a = &a;
    cout << "ptr_a = " << ptr_a << endl;

    int** ptr2_a = &ptr_a;
    cout << "ptr2_a = " << ptr2_a << endl;
    cout << "&ptr2_a = " << &ptr2_a << endl;

    // разыменование
    cout << "**ptr2_a = " << **ptr2_a << endl;
    **ptr2_a = 9;

    cout << "a = " << a << endl;

    // ==================== ссылка ===================
    cout << "==================== ссылка ===================" << endl;
    int& ref_a = a;
    cout << "ref_a = " << ref_a << endl;
    cout << "&ref_a = " << &ref_a << endl;
    ref_a = 2;
    cout << "a = " << a << endl;

    return 0;
}