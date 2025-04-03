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
	struct Node {
		Element data;
		Node* left;
		Node* right;
		int height;

		Node(const Element& el, Node* l = nullptr, Node* r = nullptr, int h = 1)
			: data(el), left(l), right(r), height(h) {}
	};
	Node* root;

public:
	AVLtree() = default;
	~AVLtree();

	Node* Insert(string key, Polinom value);  // Вставка 
	Node* Delete(string key);                 // Удаление по ключу
	Polinom* Find(string key);               // Поиск по ключу
};