/******************************************************************************
*
* While 22. Дано целое число N (> 1). Если оно является простым, то есть не 
* имеет положительных делителей, кроме 1 и самого себя, то вывести True, 
* иначе вывести False.
*
*******************************************************************************/

#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");

	int N = 9;
	if (N < 1) {
		cout << "N не является положительным."s << endl;
		return 0;
	}
	int value = 2;
	while (value < N) {
		if (N % value == 0) {
			cout << "False"s << endl;
			return 0;
		}
		++value;
	}
	cout << "True"s << endl;
	return 0;
}