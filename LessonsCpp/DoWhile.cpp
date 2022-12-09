#include <cmath>

inline int CalculateDoWhile(int n, double epsion, double& value_An) {
	int result_fact = 1; // значение факториала в знаменателе
	int numerator_to_exponent = -1; // числитель в требуемой степени
	double A_previous = 0; // предыдущее значение
	double A_current = 1 - 1 / 6; // текущее значение

	int i = 2; // индекс
	do {
		// если индекс нечетный, то -1 иначе 1
		numerator_to_exponent = i % 2 ? -1 : 1;

		// вычисляется нужное значение факториала
		int value_fact = 2 * i + 1; // знаменатель
		result_fact *= value_fact - 1;
		result_fact *= value_fact;

		// проверка на условия выхода из цикла
		if (std::abs(A_current - A_previous) < epsion) {
			value_An = A_current;
			return i;
		}

		// приращение аргументов
		A_previous = A_current;
		A_current = 1 + numerator_to_exponent / static_cast<double>(result_fact);
		++i;
	} while (i <= n);
	return -1; // код ошибки, если не был найден нужный элемент
}