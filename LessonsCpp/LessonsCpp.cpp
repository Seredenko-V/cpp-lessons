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
	//// хранит значения в единственном экземпляре, которые упорядоченны по возрастанию
	//// (от меньшего к большему). При добавлении новых элементов сортировка сохраняется
	//set<int> first_set = { 1,1,1,1,2,6,8,2 };
	//for (size_t i = 0; i < first_set.size(); ++i) {
	//	// РАЗОБРАТЬ ДОСТУП К ЭЛЕМЕНТУ
	//}
	//cout << "\n=== WORK INSERT ===\n";
	//first_set.insert(0);
	//for (const int& value : first_set) {
	//	cout << value << " ";
	//}

	/* MAP */
	map<int, string> first_map = { {0, "first"}, {1, "first"}, {0, "second"} };
	for (const auto& [key, value] : first_map) {
		cout << "key = " << key << " value = " << value << endl;
	}
	//
	cout << first_map.at(0) << endl;
	first_map[0] = "blabla"s;
	cout << first_map.at(0) << endl;
	//
	first_map[3] = "third"s;
	for (const auto& [key, value] : first_map) {
		cout << "key = " << key << " value = " << value << endl;
	}
	cout << "SIZE = " << first_map.size() << endl;

	return 0;
}