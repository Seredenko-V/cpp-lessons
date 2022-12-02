#include <iostream>
#include  <cmath>

using namespace std;

int Fact(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	return n * Fact(n - 1);
}

double CalculateFor(int n) {
	double result = 0;
	for (int i = 1; i <= n; i += 2) {
		result += 1 + (pow(-1, n) / Fact(2 * n + 1));
	}
	return result;
}

int main() {
	int value = 0;
	cin >> value;
	cout << Fact(value) << endl;

	return 0;
}