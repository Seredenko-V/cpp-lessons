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

using namespace std;

double recur(int, double&, double&, double&);

int main() {
    setlocale(LC_ALL, "Russian");
    int m;
    cout << "Введите m. m = ";
    cin >> m;

    double Y0, Y1, Y2;
    cout << "Введите Y0, Y1, Y2 -> ";
    cin >> Y0 >> Y1 >> Y2;

    double Sm = recur(m, Y0, Y1, Y2);
    cout << "Результат вычисления S" << m << ": " << Sm << endl;
    return 0;
}

double recur(int m, double& Y0, double& Y1, double& Y2) {
    double Sm = 0.0;
    for (int i = 3; i <= m; i++) {
        double Yi = cos(Y2) - 0.5 * sin(Y0) * sin(Y0);
        Sm += Yi + m / (i * i + 1);

        Y0 = Y1;
        Y1 = Y2;
        Y2 = Yi;
    }
    Sm *= m + 1 / m;
    return Sm;
}
