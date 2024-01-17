/// ЛР03. Операторы цикла: заданное число повторений. Вариант 36.
/// Задача:
/// Для заданного значения m вычислить <ФОРМУЛА>.
/// Значения m, Y0, Y1, Y2 вводятся с клавиатуры, а Yi вычисляется по формуле.
/// ==========================================================================
/// Дисклеймер:
/// Вырвиглазное решение, которое не следует никому показывать, кроме препода.
/// На практике за такое написание кода сжигают на костре.
/// Тесты не написаны ровно по той же причине, чтобы дед не гневался.
/// Правильно писать так https://google.github.io/styleguide/cppguide.html
/// ==========================================================================

#include <iostream>
#include <cmath>
#include <locale.h>

// для тестов
#include <cassert>
#include <functional>
#include <string>

using namespace std;

double for_use(int, double, double, double);
double while_use(int, double, double, double);
double do_while_use(int, double, double, double);

/// ============================= НАЧАЛО ТЕСТОВ ==============================
bool IsSameDouble(double lhs, double rhs, double epsilon = 1e-6) {
    return abs(lhs - rhs) <= epsilon;
}

void TestIsSameDouble() {
    assert(IsSameDouble(4.0000001, 4));
    assert(IsSameDouble(1.002 * 0.5, 0.501));
    cerr << "TestIsSameDouble passed\n"s;
}

void TestsCycles(const function<double(int, double, double, double)>& cycle_func, string cycle_name) {
    assert(IsSameDouble(cycle_func(0, 1.1, 1.2, 1.3), -1));
    assert(IsSameDouble(cycle_func(3, 1.1, 1.2, 1.3), 11.6));
    assert(IsSameDouble(cycle_func(5, 1.1, 1.2, 1.3), 16.678254));
    cerr << cycle_name << " passed\n"s;
}

void RunAllTests() {
    TestIsSameDouble();
    TestsCycles(for_use, "TestsFor"s);
    TestsCycles(while_use, "TestsWhile"s);
    TestsCycles(do_while_use, "TestsDoWhile"s);
    cerr << ">>> AllTests passed <<<\n"s;
}
/// ============================= КОНЕЦ ТЕСТОВ ===============================

void RunExample() {
    static int count = 1;
    cout << "Запуск примера "s << count++ << "...\n"s;
    int m;
    cout << "Введите m. m = ";
    cin >> m;

    double Y0, Y1, Y2;
    cout << "Введите Y0, Y1, Y2 -> ";
    cin >> Y0 >> Y1 >> Y2;

    double Sm = for_use(m, Y0, Y1, Y2);
    cout << "Результат вычисления S" << m << ": " << Sm << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    RunAllTests();

    char answer = 'y';
    while (answer == 'y') {
        RunExample();
        cout << "Запустить пример снова? [y/n]\n"s;
        cin >> answer;
    }
    return 0;
}

double for_use(int m, double Y0, double Y1, double Y2) {
    if (m < 1) {
        return -1; // код ошибки
    }
    int i = 0;
    double Sm = Y0 + static_cast<double>(m) / (i * i + 1); // m = 1
    i++;

    if (m > 1) { // m = 2
        Sm += Y1 + static_cast<double>(m) / (i * i + 1);
        i++;
    }
    if (m > 2) { // m = 3
        Sm += Y2 + static_cast<double>(m) / (i * i + 1);
        i++;
    }
    if (m > 3) {
        for (; i <= m; i++) { // m >= 3
            double Yi = cos(Y2) - 0.5 * sin(Y0) * sin(Y0);
            Sm += Yi + static_cast<double>(m) / (i * i + 1);

            Y0 = Y1;
            Y1 = Y2;
            Y2 = Yi;
        }
    }
    Sm *= (m + 1) / static_cast<double>(m);
    return Sm;
}

double while_use(int m, double Y0, double Y1, double Y2) {
    if (m < 1) {
        return -1; // код ошибки
    }
    int i = 0;
    double Sm = Y0 + static_cast<double>(m) / (i * i + 1); // m = 1
    i++;

    if (m > 1) { // m = 2
        Sm += Y1 + static_cast<double>(m) / (i * i + 1);
        i++;
    }
    if (m > 2) { // m = 3
        Sm += Y2 + static_cast<double>(m) / (i * i + 1);
        i++;
    }
    if (m > 3) {
        while (i <= m) { // m >= 3
            double Yi = cos(Y2) - 0.5 * sin(Y0) * sin(Y0);
            Sm += Yi + static_cast<double>(m) / (i * i + 1);

            Y0 = Y1;
            Y1 = Y2;
            Y2 = Yi;
            i++;
        }
    }
    Sm *= (m + 1) / static_cast<double>(m);
    return Sm;
}

double do_while_use(int m, double Y0, double Y1, double Y2) {
    if (m < 1) {
        return -1; // код ошибки
    }
    int i = 0;
    double Sm = Y0 + static_cast<double>(m) / (i * i + 1); // m = 1
    i++;

    if (m > 1) { // m = 2
        Sm += Y1 + static_cast<double>(m) / (i * i + 1);
        i++;
    }
    if (m > 2) { // m = 3
        Sm += Y2 + static_cast<double>(m) / (i * i + 1);
        i++;
    }
    if (m > 3) {
        do {
            double Yi = cos(Y2) - 0.5 * sin(Y0) * sin(Y0);
            Sm += Yi + static_cast<double>(m) / (i * i + 1);

            Y0 = Y1;
            Y1 = Y2;
            Y2 = Yi;
            i++;
        } while (i <= m); // m >= 3
    }
    Sm *= (m + 1) / static_cast<double>(m);
    return Sm;
}
