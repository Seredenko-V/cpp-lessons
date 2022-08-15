/******************************************************************************
*
* Потоки ввода-вывода
* https://kvodo.ru/urok-10-formatirovannyiy-vvod-vyivod-v-c.html
* https://codemore.ru/2014/02/04/cpp-streams.html
* https://metanit.com/cpp/tutorial/8.3.php
* 
*******************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Тестовый "s << flush << "вывод"s << endl;
	bool test_bool = true;
	cout << test_bool << endl;
	cout << boolalpha;
	cout << test_bool << endl;
	//int p = 64;
	//cout.unsetf(ios::dec);
	//cout.setf(ios::oct);
	//cout << "p = "s << p << endl;
	//int r = 25;
	//cout.unsetf(ios::dec);
	//cout.setf(ios::hex | ios::showbase);
	//cout << "r = " << r << endl;
	//cout.unsetf(ios::hex);
	//cout.setf(ios::dec);
	int r = 253;
	cout << "r = " << hex << r << endl;


	/* SSTREAM */
	//cout << "============== SSTREAM =============="s << endl;
	//string str = "1 2 3";
	//istringstream iss(str);
	//ostringstream oss;
	//int a, b, c;
	//iss >> a >> b >> c;
	//oss << a << endl;
	//oss << b << endl;
	//oss << c;
	//cout << oss.str();


	/* FSTREAM */
	// ВЫВОД В ФАЙЛ
	ofstream fout_first;
	fout_first.open("First_file.txt");
	if (fout_first.is_open()) {
		fout_first << "Пишем в файл"s << endl;
	}
	fout_first.close();

	// создаем и открываем файл при инициализации потока
	ofstream fout_second("Second_file.txt"); 
	fout_second << "Написали во второй файл"s << endl;
	fout_second.close();

	// ЧТЕНИЕ ИЗ ФАЙЛА
	string data;
	ifstream read_from_file;
	read_from_file.open("First_file.txt");
	string tmp;
	while (getline(read_from_file, tmp))
	{
		data += tmp;
	}
	//read_from_file >> data;
	cout << data << endl;
	read_from_file.close();
	return 0;
}