#include <iostream>

extern const int A = 2;
extern const int B = 3;

inline void Print() {
	using namespace std;
	cout << "I from new_file.cpp" << endl;
	cout << A << ' ' << B << endl;
}