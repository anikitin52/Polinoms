#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <random>
#include "Polinom.h"

class HashTable {
	size_t capacity;
	size_t a, b;
	size_t count = 0;
	const double max_full = 0.8;
	const size_t p = 1000000007;  // 10^9 + 7
	vector<list<pair<string, Polinom>>> data;

	size_t stringToNumber(const std::string& key) const;
	size_t hash(string key) const;

	void resize();

public:
	HashTable(int size);
	void Insert(string key, Polinom value);
	void Delete(string key);
	Polinom* Find(string key);
};