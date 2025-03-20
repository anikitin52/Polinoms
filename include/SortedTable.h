#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"

class SortedTable {
	struct TableLine {
		string key;
		Polinom value;
		TableLine(string _key, Polinom _value) : key(_key), value(_value) {}
	};
	vector<TableLine> data;

public:
	SortedTable() = default;

	void Insert(string key, Polinom value);
	void Delete(string key);
	Polinom Find(string key);
};