#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"

class Table {
	struct TabliceElement {
		string key;
		Polinom value;
		TabliceElement(string _key, Polinom _value) : key(_key), value(_value) {}
	};
	vector<TabliceElement> data;

public:
	class iterator {
		vector<Table::TabliceElement>::iterator it;
	public:
		explicit iterator(vector<TabliceElement>::iterator _it) : it(_it) {}

		iterator& operator++() {
			return iterator(++it);
		}

		iterator& operator++(int) {
			return iterator(it++);   // нельзя проверить вышли ли за границы
		}

		iterator& operator+(int n) {
			while (n--) {
				(*this)++;
			}
			return *this;
		}

		Polinom& value() {
			TabliceElement t_tmp = *it;
			return t_tmp.value;
		}
		string key() { return (*it).key; }

		// operator-> не имеет смысла?

		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return (it1.it != it2.it);
		}
		friend bool operator==(const iterator& it1, const iterator& it2) {
			return (it1.it == it2.it);
		}
	};

	iterator& begin() {
		auto it = data.begin();
		return iterator(it);
	}

	iterator& end() {
		return iterator(data.end());
	}

	Table() = default;
	size_t size() const noexcept { return data.size(); }
	bool Delete(string key) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i].key == key) {
				data[i] = data[data.size() - 1];
				data.pop_back();
				return true;
			}
		}
		return false;
	}
	Polinom* Find(string key) noexcept {  // const метод накладывает ограничение также и на возвращаемый тип?
		for (auto& val: data) {
			if (val.key == key) {
				return &val.value;
			}
		}
		return nullptr;
	}

	bool Insert(string key, Polinom value) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i].key == key) {
				return false;
			}
		}
		data.push_back({ key, value });
		return true;
	}
};
