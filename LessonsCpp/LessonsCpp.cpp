#include <iostream>
#include  <cmath>
#include <cassert>

using namespace std;

int Fact(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	int result = 1;
	for (int i = 2; i <= n; ++i) {
		result *= i;
	}
	return result;
}

double CalculateFor(int n, double epsion, int& number_element) {
	// заменить pow и Fact. Включить Fact внутрь этой функции
	double result = 0;
	double An_minus_one = 0;
	double An = 0;

	int value_fact_minus_one = 1;
	int value_fact = 2 * 1 + 1;

	An = 1 + (pow(-1, 1) / value_fact);

	for (int i = 1; i <= n; ++i) {

		An_minus_one = (1 + (pow(-1, i - 1) / Fact(2 * (i - 1) + 1)));
		An = (1 + (pow(-1, i) / Fact(2 * i + 1)));
		result = abs(An - An_minus_one);
		//cout << "result = " << An << " - " << An_minus_one << " = " << result << endl;
		if (result < epsion) {
			number_element = i;
			break;
		}
	}
	return An;
}

int main() {
	/*int n = 15;
	double epsilon = 8.23131e-9;
	int pos = 0;
	double value_An = CalculateFor(n, epsilon, pos);
	cout << "An = " << value_An << endl;
	cout << "pos = " << pos << endl;*/

	assert(Fact(7) == 5040);
	return 0;
}