// Задача В. Постфиксная запись

#include <iostream>
#include <vector>
#include <cassert>
#include <stack>

using namespace std;

int FindMaxAreaRectangle(vector<int> histogram) {
	histogram.push_back(0);
	int result = 0;
	stack<int> index_stack;
	for (int i = 0; i < histogram.size(); ++i) {
		while (!index_stack.empty() && histogram[i] < histogram[index_stack.top()]) {
			int top = index_stack.top();
			index_stack.pop();
			int nextTop = index_stack.size() == 0 ? -1 : index_stack.top();
			result = max((i - nextTop - 1) * histogram[top], result);
		}
		index_stack.push(i);
	}
	return result;
}

void Test() {
	vector<int> values = { 2,1,4,5,1,3,3 };
	assert(FindMaxAreaRectangle(values) == 8);

	values = { 2,1,2 };
	assert(FindMaxAreaRectangle(values) == 3);

	values = { 0 };
	assert(FindMaxAreaRectangle(values) == 0);
	cout << "All tests passed"s << endl;
}

int main() {
	Test();

	return 0;
}