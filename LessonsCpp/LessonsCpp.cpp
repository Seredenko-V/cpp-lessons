/***************************************************************
    Лабораторная работа 3. Вариант 8
    Изучение циклических алгоритмов, операторов цикла,
    программирование циклического вычислительного процесса

    Задание 1. Вычислить и вывести на экран или в файл в виде таблицы
    значения функции, заданной графически, на интервале от Xнач до Xкон с
    шагом dx. Интервал и шаг задать таким образом, чтобы проверить все ветви
    программы. Таблица должна иметь заголовком и шапку.

***************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int Xbegin = -10;
    int Xend = 8;
    double dx = 1; // шаг приращения

    cout << "Table 1 - Function values"s << endl;
    cout << "    x"s << "\t"s << "    y"s << endl;

    // ========================= окружность =========================
    int x_end_circle = -6;
    // координаты центра окружности
    int x_center_circle = -8;
    int y_center_circle = -2;
    int R = 2; // радиус окружности

    for (double x = Xbegin; x < x_end_circle; x += dx) {
        cout << x << "\t|"s << sqrt(R * R - pow(x - x_center_circle, 2)) + y_center_circle << endl;
    }

    // ========================= первая прямая =========================
    int x_begin_line = x_end_circle;
    int x_end_line = 2;
    int y_begin_line = -2;
    int y_end_line = 2;
    for (double x = x_begin_line; x < x_end_line; x += dx) {
        cout << x << "\t|"s << (x - x_begin_line) * (y_end_line - y_begin_line) / (x_end_line - x_begin_line) + y_begin_line << endl;
    }

    // ========================= вторая прямая =========================
    int x_begin_zero_line = x_end_line;
    int x_end_zero_line = 6;
    int y_begin_zero_line = 0;
    int y_end_zero_line = 0;
    for (double x = x_begin_zero_line; x < x_end_zero_line; x += dx) {
        cout << x << "\t|"s << (x - x_begin_zero_line) * (y_end_zero_line - y_begin_zero_line) / (x_end_zero_line - x_begin_zero_line) + y_begin_zero_line << endl;
    }

    // ========================= парабола =========================
    int x_begin_parabola = x_end_zero_line;
    for (double x = x_begin_parabola; x <= Xend; x += dx) {
        cout << x << "\t|"s << pow(x - 6, 2) << endl;
    }

    return 0;
}
