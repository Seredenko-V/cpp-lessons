/******************************************************************************
* 
* Абрамян М. Э.
* For 36. Даны целые положительные числа N и K. Найти сумму 1^K + 2^K + … + N^K. 
* Чтобы избежать целочисленного переполнения, вычислять слагаемые этой суммы с
* помощью вещественной переменной и выводить результат как вещественное число.
* 
*******************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	int N = 2;
	int K = 12;
	if (N <= 0 || K <= 0) {
		cout << "N и K должны быть больше 0"s << endl;
		return 0;
	}
	double result = 0;
	double check = 0;
	for (int i = 1; i <= N; ++i) {
		check += pow(i, K);
		double mult = 1;
		for (int j = 1; j <= K; ++j) {
			mult *= i;
		}
		result += mult;
	}
	cout << "Результат = "s << result << endl;
	cout << "Проверка (pow(i, K)) = "s << check << endl;
	return 0;
}