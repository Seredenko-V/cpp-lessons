/******************************************************************************
* 
* Абрамян М. Э.
* For 23. Дано вещественное число X и целое число N (> 0). Найти значение 
* выражения X — X^3/(3!) + X^5/(5!) -…+ (-1)^N*X^(2*N+1)/((2*N+1)!) 
* (N! = 1*2*…*N). Полученное число является приближенным значением функции 
* sin в точке X.
* 
*******************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	int N = 2;
	if (N <= 0) {
		cout << "N должно быть больше 0"s << endl;
		return 0;
	}

	double X = 7.3;
	double result = 0;
	double fact = 1;
	for (size_t i = 0; i < static_cast<size_t>(N); ++i) {
		size_t value_for_fact = (2 * i + 1);
		for (size_t j = 1; j <= value_for_fact; ++j) {
			fact *= j;
		}
		result += pow(-1, i) * pow(X, 2 * i + 1) / fact;
		fact = 1;
	}
	cout << "Результат = "s << result << endl;
	return 0;
}