#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"

class SortedTable {
	struct TableLine {
		string key;        // Ключ (сторка)
		Polinom value;     // Значение (полином)
		TableLine(string _key, Polinom _value) : key(_key), value(_value) {}
	};
	vector<TableLine> data;
	
public:
	SortedTable() = default;
	void Insert(string key, Polinom value);  // Вставка 
	void Delete(string key);                 // Удаление по ключу
	Polinom* Find(string key);               // Поиск по ключу
};
