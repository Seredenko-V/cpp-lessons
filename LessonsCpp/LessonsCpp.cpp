// Задача В. Постфиксная запись

#include <iostream>
#include <string>
#include <cassert>
#include <set>
#include <stack>
#include <cctype>

using namespace std;

int CalculatePostfixEntry(const string& input) {
	stack<int> operands;
	for (size_t i = 0; i < input.size(); ++i) {
		if (input[i] == ' ') {
			continue;
		}

		if (isdigit(input[i])) {
			operands.push(input[i] - '0');
		} else {
			int rhs = operands.top();
			operands.pop();
			int lhs = operands.top();
			operands.pop();

			switch (input[i]) {
				case '+':
					operands.push(lhs + rhs);
					break;
				case '-':
					operands.push(lhs - rhs);
					break;
				case '*':
					operands.push(lhs * rhs);
					break;
				case '/':
					operands.push(lhs / rhs);
					break;
				default:
					break;
			}
		}
	}
	return operands.top();
}

void Test() {
	string text = "8 9 +"s;
	assert(CalculatePostfixEntry(text) == 17);

	text = "2 5 3 + 6 * +"s;
	assert(CalculatePostfixEntry(text) == 50);

	text = "8 2 5 * + 1 3 2 * + 4 - /"s;
	assert(CalculatePostfixEntry(text) == 6);
	cout << "All tests passed"s << endl;
}

int main() {
	Test();

	return 0;
}