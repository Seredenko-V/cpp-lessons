#include <iostream>

using namespace std;

class Point {
public:

	Point() = default;

	Point(int value_x, int value_y) : x_(value_x), y_(value_y) {
	}

	explicit Point(int value_x) : x_(value_x) {
	}

	// конструктор копирования
	Point(const Point& other) {
		this->x_ = other.x_;
		this->y_ = other.y_;
	}

	// оператор присваивания
	Point& operator= (const Point& other) {
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

	// деструктор
	~Point() = default;

	int GetX() const;
	int GetY() const;

private:
	int x_ = 0;
	int y_ = 0;
};

int Point::GetX() const {
	return x_;
}

int Point::GetY() const {
	return y_;
}

double& Foo(double num) {
	double a = 2;
	return num;
}

int main() {
	Point first(6, 2);
	cout << first.GetX() << '\t' << first.GetY() << endl;
	cout << "&first = " << &first << endl;
	Point second(first);
	cout << second.GetX() << '\t' << second.GetY() << endl;
	cout << "&second = " << &second << endl;
	first = { -1, -5 };
	cout << first.GetX() << '\t' << first.GetY() << endl;
	cout << "&first = " << &first << endl;

	int value = 23;
	double b = Foo(value);
	cout << ++b << endl;


	return 0;
}