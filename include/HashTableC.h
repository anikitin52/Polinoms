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
	size_t hash(string key);

	void resize() {
		size_t newCapacity = capacity * 2;
		vector<list<pair<string, Polinom>>> newData(newCapacity);
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(1, p - 1);

		a = dist(gen);
		b = dist(gen);
		
		capacity = newCapacity;
		
		for (auto& chain : data) {
			for (auto& list : chain) {
				size_t newIndex = hash(list.first);
				newData[newIndex].push_back(list);
			}
		}
		data = std::move(newData);
		capacity = newCapacity;
		
	}

public:
	HashTable(int size);
	void Insert(string key, Polinom value);
	void Delete(string key);
	Polinom Find(string key);
};