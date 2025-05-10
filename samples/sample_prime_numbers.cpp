#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include "SortedTable.h"

using namespace std;

vector<string> databases;


void create_database() {
	string name;
	cout << "Введите название базы данных: ";
	cin >> name;
	ofstream file(name + ".txt");
	databases.push_back(name);
	if (!file.is_open()) { // Проверка открытия файла
		cerr << "Ошибка открытия файла\n";
		return;
	}
	cout << "База данных создана!";
}

void open_database() {
	cout << "Выберие базу данных: ";
	for (int i = 1; i <= databases.size(); i++) {
		cout << i << " " << databases[i];
	}
	int dbnum;
	cin >> dbnum;

}



int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Приветствие \n";
	int step1;
	while (step1 != 3) {
		cout << "1 - Создать базу данных \n2 - Открыть существующую базу данных \n3 - Выход \n Ввод: ";
		cin >> step1;
		if (step1 == 1) create_database();
		else if (step1 == 2) open_database();
		else cout << "Ошибка!";
	}

	return 0;
}
