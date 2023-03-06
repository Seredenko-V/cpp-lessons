#include <iostream>
#include <vector>
#include <string>

using namespace std;

class People {
public:
	People() {
		cout << "Constructor default"s << endl;
	}

	People(int age) {
		cout << "Constructor 1"s << endl;
		age_ = age;
		if (age >= 18) {
			adult_ = true;
		}
	}

	People(int age, const string& name) {
		cout << "Constructor 2"s << endl;
		age_ = age;
		if (age >= 18) {
			adult_ = true;
		}
		name_ = name;
	}

	bool IsAbult() const {
		return adult_;
	}

	~People() {
		cout << "Destructor"s << endl;
	}
private:
	int age_ = 0;
	bool adult_ = false;
	string name_ = "no name"s;
};

int main() {
	People first(20, "Petr"s);
	if (first.IsAbult()) {
		cout << "IsAbult"s << endl;
	} else {
		cout << "Baby"s << endl;
	}

	return 0;
}