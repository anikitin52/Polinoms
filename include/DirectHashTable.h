#pragma once
#include <iostream>
#include "Polinom.h"

template<int SIZE>
class HashTable {
	tuple<string, Polinom, bool, bool> *Rows;
	//tuple<2> - actual/default
	//tuple<3> - not delete/delete
	unsigned int size_table;
	unsigned int p;
	unsigned int actual_size_table;

	// SIZE - число, на которое будет увеличиваться размер таблицы при каждой перепаковке, и первый размер таблицы

public:
	class iterator {
		tuple<string, Polinom, bool, bool>* it;
	public:
		iterator(tuple<string, Polinom, bool, bool>* _it): it(_it) {}
		iterator& operator++() {
			if (std::get<0>(*it) == "END") throw 1;
			it += 1;
			while (!(std::get<2>(*it)) && (std::get<0>(*it) != "END")) {
				it += 1;
			}
			return *this;
		}

		iterator operator++(int) {
			iterator tmp = *this;
			if (std::get<0>(*it) == "END") { throw 1; }
			it += 1;
			while (!std::get<2>(*it) && (std::get<0>(*it) != "END"))
			{
				it += 1;
			}
			return tmp;
		}

		iterator& operator+(int n) {
			while (n--) {
				(*this)++;
			}
			return *this;
		}

		Polinom& operator*() {
			if (std::get<0>(*it) == "END") throw 1;
			return std::get<1>(*it);
		}

		Polinom* operator->() {
			if (std::get<0>(*it) == "END") throw 1;
			return std::get<2>(*it);
		}

		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return (it1.it != it2.it);
		}

		friend bool operator==(const iterator& it1, const iterator& it2) {
			return (it1.it == it2.it);
		}
	};

	iterator& begin() {  // можно не const?
		if (actual_size_table == 0) return end();
		if (std::get<2>(Rows[size_table])) return iterator(&Rows[0]);
		return ++iterator(&Rows[0]);
	}

	iterator& end() const {
		return iterator(&Rows[size_table]);
	}

	HashTable() : Rows(nullptr), size_table(SIZE), actual_size_table(0), p(7){
		Rows = new tuple<string, Polinom, bool, bool>[size_table + 1];
		std::get<0>(Rows[size_table]) = "END";
		// как использовать функцию, которая не относится к самому классу, но нужна в методах
	}

	// FLAGI
	// constr RGB

	HashTable(const HashTable& other) {
		size_table = other.size_table;
		p = other.p;
		actual_size_table = other.actual_size_table;
		Rows = new tuple<string, Polinom, bool, bool>[size_table + 1];
		std::get<0>(Rows[size_table]) = "END";
		for (int i = 0; i < size_table; i++) {
			Rows[i] = other.Rows[i];
		}
	}

	HashTable& operator=(const HashTable& other) {
		if (this == &other) return *this;
		delete[] Rows;
		size_table = other.size_table;
		p = other.p;
		actual_size_table = other.actual_size_table;
		Rows = new tuple<string, Polinom, bool, bool>[size_table + 1];
		std::get<0>(Rows[size_table]) = "END";
		for (int i = 0; i < size_table; i++) {
			Rows[i] = other.Rows[i];
		}
		return *this;
	}

	~HashTable() {
		delete[] Rows;
	}

	int h(string key) {
		int key2 = 0;
		for (char ch: key) {
			key2 += ch;
		}
		return key2 % size_table;
	}

	int hh(int key) {
		return (key + p) % size_table;
	}
	//perepakovka
	bool Insert(string key, Polinom value) {
		int hash_key = h(key);
		while (1) {
			if (!(std::get<2>(Rows[hash_key]))) {
				Rows[hash_key] = { key, value, 1, 0 };
				actual_size_table += 1;
				float koef = ((float)actual_size_table)/((float)size_table);

				if (koef >= 0.8) {
					// perepakovka
					size_table = size_table + SIZE;
					actual_size_table = 0;
					tuple<string, Polinom, bool, bool>* Rows2 = Rows;
					Rows = new tuple<string, Polinom, bool, bool>[size_table];
					for (int i = 0; i < size_table - SIZE; i++) {
						if (std::get<2>(Rows2[i])) {
							Insert(std::get<0>(Rows2[i]), std::get<1>(Rows2[i]));
						}
					}
					delete[] Rows2;
				}
				return true;
			}
			if (std::get<2>(Rows[hash_key]) && ((std::get<0>(Rows[hash_key])) == key)) return false; // dublirovanie
			hash_key = hh(hash_key);
		}
		return false;
	}

	bool Delete(string key) {
		int hash_key = h(key);
		while (1) { // таблица всегда имеет коэф <= 0.8 ---> всегда будет выход из цикла
			if (std::get<2>(Rows[hash_key])) {
				if ((std::get<0>(Rows[hash_key])) == key) {
					std::get<2>(Rows[hash_key]) = 0;
					std::get<3>(Rows[hash_key]) = 1;
					actual_size_table -= 1;
					return true;
				}
			}
			if (!std::get<3>(Rows[hash_key])) {
				return false; // не нашли 
			}
			hash_key = hh(hash_key);
		}
	}

	Polinom* Find(string key) {
		int hash_key = h(key);
		while (1) { // таблица всегда имеет коэф <= 0.8 ---> всегда будет выход из цикла
			if (std::get<2>(Rows[hash_key])) {
				if ((std::get<0>(Rows[hash_key])) == key) {
					return &(std::get<1>(Rows[hash_key])); // возвращаем ссылку
				}
			}
			if (!std::get<3>(Rows[hash_key])) {
				return nullptr; // не нашли 
			}
			hash_key = hh(hash_key);
		}
	}

	int GetActualSize() const { return actual_size_table; }
	int GetSize() const { return size_table; }
};