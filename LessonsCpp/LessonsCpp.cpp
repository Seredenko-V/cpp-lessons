#include <iostream>
#include  <cmath>
#include <cassert>

using namespace std;

int Fact(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	return n * Fact(n - 1);
}

double CalculateFor(int n, double epsion) {
	double result = 0;
	int number_element = 0;
	double An_minus_one = 0;
	double An = 0;

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
	cout << "An = " << An << endl;
	cout << "pos = " << number_element << endl;
	return An;
}

int main() {
	//int value = 0;
	//cin >> value;
	//cout << Fact(value) << endl;

	return 0;
}