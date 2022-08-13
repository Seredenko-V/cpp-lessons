/******************************************************************************
*
* Контейнеры STL
*
*******************************************************************************/

#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iterator>

using namespace std;

// перегрузка оператора вывода для std::vector
template <typename Type>
ostream& operator<<(ostream& out, vector<Type> str) {
	for (const Type& c : str) {
		out << c;
	}
	return out;
}

int main() {
	setlocale(LC_ALL, "ru");
	/* VECTOR */
	//vector<int> first(10);
	//iota(first.begin(), first.end(), 0);
	//cout << first.size() << endl;
	//for (size_t i = 0; i < first.size(); ++i) {
	//	cout << first[i] << " ";
	//}
	//cout << endl << "=============" << endl;
	//first.resize(5);
	//cout << first.size() << endl;
	//for (size_t i = 0; i < first.size(); ++i) {
	//	cout << first[i] << " ";
	//}
	//first[3] = 99;
	//cout << endl << "=============" << endl;
	//for (size_t i = 0; i < first.size(); ++i) {
	//	cout << first[i] << " ";
	//}


	/* STRIGN */
	//vector<char> = string
	//vector<string> strings;
	//strings.reserve(2);
	//strings.push_back("hello"s);
	//strings.push_back("word"s);
	//for (const string& c : strings) {
	//	cout << c << endl;
	//}
	//==========================================
	//string second = {"cat dog test word"};
	//string third;
	//third = second;
	//for (size_t i = 0; i < second.size(); ++i) {
	//	if (second[i] == 'g') {
	//		cout << "g лежит в " << i << " элементе" << endl;
	//	}
	//}
	//cout << second[second.find('g')] << endl;
	//cout << "\n=== Work substr ===\n";
	//// 4 - начиная с какого момента, 1 - сколько букв после 4 вывести
	//string sub_second = second.substr(4, 1);
	//cout << sub_second << endl;


	/* SET */
	// хранит значения в единственном экземпляре, которые упорядоченны по возрастанию
	// (от меньшего к большему). При добавлении новых элементов сортировка сохраняется
	set<int> first_set = { 1,1,1,1,2,6,8,2 };
	// доступ к элементам через итераторы
	for (set<int>::iterator it = first_set.begin(); it != first_set.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	// или можно обратиться к конкретному элементу так:
	size_t index_element = 2;
	if (index_element >= first_set.size()) {
		cout << "Недопустимое значение индекса"s << endl;
	} else {
		set<int>::iterator it_element = next(first_set.begin(), index_element);
		cout << "Элемент set с индексом "s << index_element << " = "s << *it_element << endl;
	}
	// НО так никто почти не делает, т.к. у set двунаправленные итераторы, 
	// а не произвольного доступа, см. https://habr.com/ru/post/122283/
	
	// если интересует какой-то конкретный элемент:
	int value = 9;
	set<int>::iterator it_value = find(first_set.begin(), first_set.end(), value);
	if (it_value != first_set.end()) {
		cout << "Через std::find = "s << *it_value << endl;
	} else {
		cout << "Элемент "s << value << " в first_set отсутствует"s << endl;
	}
	cout << "\n=== WORK INSERT ===\n"s;
	first_set.insert(0);
	for (const int& value : first_set) {
		cout << value << " ";
	}

	/* MAP */
	//map<int, string> first_map = { {0, "first"}, {1, "first"}, {0, "second"} };
	//for (const auto& [key, value] : first_map) {
	//	cout << "key = " << key << " value = " << value << endl;
	//}
	////
	//cout << first_map.at(0) << endl;
	//first_map[0] = "blabla"s;
	//cout << first_map.at(0) << endl;
	////
	//first_map[3] = "third"s;
	//for (const auto& [key, value] : first_map) {
	//	cout << "key = " << key << " value = " << value << endl;
	//}
	//cout << "SIZE = " << first_map.size() << endl;


	/* LIST */
	//https://ru.cppreference.com/w/cpp/container/list
	list<int> first_list = { 5, 6, 7, 12, 99, 10 };
	first_list.push_back(5);
	first_list.push_front(0);
	first_list.insert(next(first_list.begin(), 2), 4);
	cout << "\n=================== LIST ===================\n"s;
	for (const int& value : first_list) {
		cout << value << " ";
	}
	cout << endl;
	// если нам нужен, например, 7 элемент двунаправленного списка, то:
	cout << "first_list[7] = "s << *next(first_list.begin(), 7) << endl;
	*next(first_list.begin(), 7) = 23;
	for (const int& value : first_list) {
		cout << value << " ";
	}
	cout << endl;
	cout << "first_list.size() = "s << first_list.size() << endl;
	return 0;
}