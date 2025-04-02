#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"

class AVLtree {
	struct Element {
		string key;
		Polinom value;
		Element(string _key, Polinom _value) : key(_key), value(_value) {}
	};
	vector<Element> data;

public:
	AVLtree() = default;
	void Insert(string key, Polinom value);  // Вставка 
	void Delete(string key);                 // Удаление по ключу
	Polinom* Find(string key);               // Поиск по ключу
};