﻿/******************************************************************************
*
* Proc 16. Описать функцию Sign(X) целого типа, возвращающую для веществен-
* ного числа X следующие значения: –1, если X < 0; 0, если X = 0; 1, если X > 0
* С помощью этой функции найти значение выражения Sign(A) + Sign(B) для
* данных вещественных чисел A и B.
*
*******************************************************************************/

#include <iostream>

using namespace std;

int Sign(double X) {
	if (X < 0) {
		return -1;
	}
	if (X > 0) {
		return 1;
	} 
	return 0;
}

int main() {
	setlocale(LC_ALL, "ru");
	double A = 52.0213;
	double B = -1;
	cout << Sign(A) + Sign(B) << endl;

	return 0;
}