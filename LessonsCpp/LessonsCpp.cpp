/******************************************************************************
*
* 25. Создайте шаблонный класс матриц. Определите в нем конструкторы и 
* деструктор. Определите дружественные функции сложение и умножение матриц. 
* Проиллюстрировать работу для целых и вещественных матриц.
*
*******************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <type_traits>
#include <cassert>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename Type>
class Matrix {
public:
	Matrix() = default;

	// Матрица заданной размерности заполняется значением по умолчанию
	Matrix(const size_t num_strings, const size_t num_columns) 
	: Matrix(num_strings, num_columns, Type()) {
	}

	// Матрица с заданной размерностью заполняется значением value
	Matrix(const size_t num_strings, const size_t num_columns, const Type& value)
	: num_strings_(num_strings)
	, num_columns_(num_columns)
	, matrix_(num_strings, vector<Type>(num_columns, value)) {
	}

	// Инициализация матрицы через список инициализации
	Matrix(initializer_list<initializer_list<Type>> init) 
	: matrix_(init.size()) {
		size_t num_str = 0;
		set<size_t> number_columns; // количество столбцов в каждой строке
		for (const initializer_list<Type>& column : init) {
			matrix_[num_str++] = column;
			number_columns.insert(column.size());
		}

		// проверка матрицы на "прямоугольность"
		try {
			if (number_columns.size() > 1) {
				throw invalid_argument("Некорректно задана матрица через список инициализации."s);
			}
		} catch (exception& except) {
			cout << except.what() << endl;
			matrix_.clear();
			matrix_.resize(0);
		}
	}

	// Такой деструктор бестолковый. Его реализация нужна лишь в том случае,
	// если имеем дело с динамической памятью
	~Matrix() {
		for (vector<Type>& column : matrix_) {
			column.clear();
			column.resize(0);
		}
		matrix_.clear();
		matrix_.resize(0);
		num_strings_ = 0;
		num_columns_ = 0;
	}

	template <typename Type>
	friend void PrintMatrix(const Matrix<Type>& matrix);
	template <typename Type>
	friend Matrix<Type> AdditionMatrix(const Matrix<Type>& lhs, const Matrix<Type>& rhs);
	template <typename Type>
	friend Matrix<Type> MultiplicationMatrix(const Matrix<Type>& lhs, const Matrix<Type>& rhs);

private:
	static_assert(is_arithmetic_v<Type>); // тип данных матрицы - числа
	size_t num_strings_;
	size_t num_columns_;
	vector<vector<Type>> matrix_;
};

template <typename Type>
void PrintMatrix(const Matrix<Type>& matrix) {
	for (const vector<Type>& column : matrix.matrix_) {
		for (const Type& value : column) {
			cout << value << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename Type>
Matrix<Type> AdditionMatrix(const Matrix<Type>& lhs, const Matrix<Type>& rhs) {
	try {
		if (lhs.num_strings_ != rhs.num_strings_ || lhs.num_columns_ != rhs.num_columns_) {
			throw invalid_argument("Сложение невозможно, т.к. размерности матриц должны быть одинаковыми."s);
		}
		Matrix<Type> result(lhs.num_strings_, lhs.num_columns_);
		for (size_t str = 0; str < result.num_strings_; ++str) {
			for (size_t col = 0; col < result.num_columns_; ++col) {
				result.matrix_[str][col] = lhs.matrix_[str][col] + rhs.matrix_[str][col];
			}
		}
		return result;
	} catch (exception& except) {
		cout << except.what() << endl;
		return {};
	}
}

template <typename Type>
Matrix<Type> MultiplicationMatrix(const Matrix<Type>& lhs, const Matrix<Type>& rhs) {
	try {
		if (lhs.num_columns_ != rhs.num_strings_) {
			throw invalid_argument("Умножение не возмножно, так как количество столбцов 1-ой матрицы не равно \nколичеству строк 2-ой матрицы."s);
		}
		Matrix<Type> result(lhs.num_strings_, rhs.num_columns_);
		/* Самостоятельно */
	} catch (exception& except) {
		cout << except.what() << endl;
		return {};
	}

}

int main() {
	setlocale(LC_ALL, "ru");
	Matrix<double> first(2, 2, 5.3);
	PrintMatrix(first);
	Matrix<double> second(2, 2, 1.2);
	PrintMatrix(second);
	Matrix third = { { 1,2,3 }, { 4,5,6 } };
	PrintMatrix(third);

	PrintMatrix(AdditionMatrix(first, second));
	//PrintMatrix(MultiplicationMatrix(first, second));
	return 0;
}