#include <iostream>
#include <cmath>

#include "While.cpp"
#include "DoWhile.cpp"

using namespace std;

int CalculateFor(int n, double epsion, double& value_An) {
	int result_fact = 1; // значение факториала в знаменателе
	int numerator_to_exponent = -1; // числитель в требуемой степени
	double A_previous = 0; // предыдущее значение
	double A_current = 1 - 1 / 6; // текущее значение

	for (int i = 2; i <= n; ++i) {
		// если индекс нечетный, то -1 иначе 1
		numerator_to_exponent = i % 2 ? -1 : 1;
		
		// вычисляется нужное значение факториала
		int value_fact = 2 * i + 1; // знаменатель
		result_fact *= value_fact - 1;
		result_fact *= value_fact;

		// проверка на условия выхода из цикла
		if (abs(A_current - A_previous) < epsion) {
			value_An = A_current;
			return i;
		}
		
		// приращение аргументов
		A_previous = A_current;
		A_current = 1 + numerator_to_exponent / static_cast<double>(result_fact);
	}
	return -1; // код ошибки, если не был найден нужный элемент
}

int main() {
	setlocale(LC_ALL, "ru");
	int n = 2;
	double epsilon = 0;
	double result = 0; // искомое значение
	int pos = 0; // его позиция
	char symbol = ' ';

	while (true) {
		cout << "n = "s;
		cin >> n;
		if (n < 2) {
			cout << "Ошибка. n должно быть не меньше 2"s << endl;
			continue;
		}

		cout << "epsilon = "s;
		cin >> epsilon;
		if (epsilon > 1 || epsilon <= 0) {
			cout << "Ошибка. epsilon должно быть в пределах (0, 1]"s << endl;
			continue;
		}

		cout << "Варианты действий:"s << endl;
		cout << "f - реализация циклом for;"s << endl;
		cout << "w - реализация циклом while;"s << endl;
		cout << "d - реализация циклом do while;"s << endl;
		cout << "любой другой символ - выход."s << endl;
		cin >> symbol;

		switch (symbol) {
			case 'f':
				pos = CalculateFor(n, epsilon, result);
				break;
			case 'w':
				pos = CalculateWhile(n, epsilon, result);
				break;
			case 'd':
				pos = CalculateDoWhile(n, epsilon, result);
				break;
			default:
				return 0;
				break;
		}

		if (pos < 0) {
			cout << "Значение не было найдено. Нужно увеличить epsilon или n"s << endl;
			continue;
		}
		cout << "Искомое начение: "s << result << endl;
		cout << "Его номер: "s << pos << endl;

		
		cout << "======================================="s << endl;
	}

	return 0;
}