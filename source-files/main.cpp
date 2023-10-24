#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/// ЛР01. Поразрядные операции. Вариант 36

class Object {
public:
    Object() {
        cout << "Constructor "s << this << endl;
        double* d = new double[10'000];
    }
    ~Object() {
        cout << "Destructor "s << this << endl;
    }

};

int main() {
    while (true) {
        Object* a = new Object;
    }
    return 0;
}
