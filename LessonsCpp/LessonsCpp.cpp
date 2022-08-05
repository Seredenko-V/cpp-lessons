/******************************************************************************
* 
* Класс MyVector с динамическим одномерным массивом
* Конструктор по умолчанию, конструктор с параметром,
* деструктор, оператор присваивания.
* 
*******************************************************************************/

#include <iostream>

using namespace std;

template <typename Type>
class MyVector {
public:
	MyVector() noexcept = default;

	// вызываем другой конструктор (для минимизации строк кода)
	explicit MyVector(size_t size) 
	: MyVector(size, Type()) {
	}

	MyVector(size_t size, const Type& value) 
	: size_(size)
	, capacity_(size) {
		my_vector_ = new Type[size];
		for (size_t i = 0; i < size; ++i) {
			my_vector_[i] = value;
		}
	}

	// Конструктор копирования
	MyVector(const MyVector& other) 
	: size_(other.size_) 
	, capacity_(other.capacity_) {
		my_vector_ = new Type[size_];
		for (size_t i = 0; i < size_; ++i) {
			this->my_vector_[i] = other.my_vector_[i];
		}
	}

	~MyVector() {
		delete[] my_vector_;
		size_ = 0;
	}

	MyVector& operator=(const MyVector& rhs) {
		if (this->my_vector_ == rhs.my_vector_) {
			return *this;
		}
		this->size_ = rhs.size_;
		// проверка на наличие данных в текущем векторе
		if (this->my_vector_ != nullptr) {
			delete[] my_vector_;
		}
		this->my_vector_ = new Type[size_];
		for (size_t i = 0; i < size_; ++i) {
			this->my_vector_[i] = rhs.my_vector_[i];
		}
		return *this;
	}

	void Print() {
		for (size_t i = 0; i < size_; ++i) {
			cout << my_vector_[i] << " "s;
		}
		cout << endl;
	}

private:
	size_t size_ = 0;
	size_t capacity_ = 0;
	Type* my_vector_ = nullptr;
};

int main() {
	setlocale(LC_ALL, "ru");

	MyVector<int> first(5, 2);
	cout << "first = "s;
	first.Print();

	MyVector<int> second(2, 9);
	cout << "second = "s;
	second.Print();

	first = second;
	cout << "first = "s;
	first.Print();

	return 0;
}