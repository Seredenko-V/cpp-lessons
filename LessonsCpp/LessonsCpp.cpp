/*******************************************************************************
	Тесты
*******************************************************************************/

#include <iostream>
#include <cassert>

using namespace std;

int SumArr(int arr[], int size) {
	return 0;
}


int main() {
	setlocale(LC_ALL, "ru");
	const int SIZE = 5;
	int arr_first[SIZE] = { 1,2,3,4,5 };
	int arr_second[SIZE] = { 9,8,7,6,5 };
	int arr_result[SIZE];
	for (int i = 0; i < SIZE; ++i) {
		arr_result[i] = arr_first[i] + arr_second[i];
		assert(arr_result[i] == 10);
		cout << "ok" << endl;
	}


	return 0;
}