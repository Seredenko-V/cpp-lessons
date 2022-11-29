#include <iostream>

using namespace std;

double Calculate(double b, double c, double d, double q, double r, int n) {
	double X0 = b;
	double X1 = c;
	if (n == 2) {
		return X1;
	}

	double Xn = 0;
	int k = 2;
	while (k < n) {
		Xn = d * X1 + q * X0 + r;
		cout << Xn << endl;
		X0 = X1;
		X1 = Xn;
		++k;
	}

	return Xn;
}

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Реализация while" << endl;

	double b = 2;
	double c = 4;
	double d = 5;
	double q = 1;
	double r = 7;
	int n = 2;

	if (n < 2) {
		cout << "Error. n < 2" << endl;
		return 1;
	}

	cout << "Функция вернула " << Calculate(b, c, d, q, r, n) << endl;
	
	char sol_continue;
	while (true) {
		cout << "Желаете посчитать еще раз? [y/n]" << endl;
		cin >> sol_continue;
		if (sol_continue == 'y') {
			cout << "b = ";
			cin >> b;
			// тут нужно ввести остальные переменные заново
			cout << "Функция вернула " << Calculate(b, c, d, q, r, n) << endl;
		} else {
			break;
		}
	}
}