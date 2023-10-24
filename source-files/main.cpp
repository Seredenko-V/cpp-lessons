#include <iostream>
#include <stack>
#include <list>
#include <string>

using namespace std;

template <typename T>
class Stack {
    // реализация))
};

bool IsAddMessage(const string& query) {
    return query.front() == '+' ? true : false;
}

// Нужна т.к. в после числа есть '\n' и следующее считывание
// наткнется на этот символ и получится пустая строка
int ReadNumber(istream& in) {
    string empty;
    int number = 0;
    in >> number;
    getline(in, empty);
    return number;
}

int main() {
    stack<uint32_t> messages;
    list<uint32_t> deleted_messages;
    cout << "Enter num operation "s;
    int num_operation = ReadNumber(cin);
    string query;

    while(num_operation-- > 0) {
        getline(cin, query);
        if (IsAddMessage(query)) {
            int value = stoi(query.substr(2));
            messages.push(value);
        } else {
            if (!messages.empty()) {
                deleted_messages.push_back(messages.top());
                messages.pop();
            }
        }
    }

    cout << "\nDeleted messages:\n"s;
    for (uint32_t message : deleted_messages) {
        cout << message << endl;
    }

    return 0;
}
