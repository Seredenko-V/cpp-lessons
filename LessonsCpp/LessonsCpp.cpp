#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& vec) {
	for (int value : vec) {
		out << value << ' ';
	}
	return out;
}

void Reverse(vector<int>& elements) {
	size_t size = elements.size();
	for (size_t i = 0; i < size / 2; ++i) {
		int tmp = elements[i];
		elements[i] = elements[size - 1 - i];
		elements[size - 1 - i] = tmp;
	}
}

void Test() {
	{
		vector<int> etalon{ -3, 5, 9, 0, 6, 8, 4, 1 };
		vector<int> elements = etalon;
		vector<int> reverse_elem{ 1,4,8,6,0,9,5,-3 };
		Reverse(elements);
		assert(elements == reverse_elem);
		Reverse(elements);
		assert(elements == etalon);
	}
	{
		vector<int> elements{ 1,2,3,4,5 };
		vector<int> reverse_elem{ 5,4,3,2,1 };
		Reverse(elements);
		assert(elements == reverse_elem);
	}
	{
		vector<int> elements{ 1,1,1,1,1,1,1 };
		vector<int> reverse_elem = elements;
		Reverse(elements);
		assert(elements == reverse_elem);
	}
}

int main() {
	Test();
	return 0;
}