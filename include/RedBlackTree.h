#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"


class RedBlackTree {
	enum class Color { Red, Black };

	struct Node {
		string key;
		Node* left, * right, * parent;  // по умолчанию nullptr?
		Color color = Color::Black;
		Polinom* data = nullptr;
		~Node() {
			if (!data) return;
			delete data;
			delete left; delete right;  // correct distructor?
		}
		Node* Sibling() {
			if (!parent) return nullptr;
			Node* sibling;

			if (parent->left != this) sibling = parent->left;
			else sibling = parent->right;

			return sibling;

		}

		Node* Grandparent() {
			return this->parent->parent;

		}

		Node* Uncle() {
			Node* grandparent = this->parent->parent;
			Node* uncle;
			if (grandparent->right != parent) uncle = grandparent->right;
			else uncle = grandparent->left;

			return uncle;
		}

		Node* RSibling() {
			if (!parent) return nullptr;
			Node* sibling;

			if (parent->left != this) sibling = parent->left;
			else sibling = parent->right;

			if (!(sibling->data)) throw 1;
			return sibling->right;

		}

		Node* LSibling() {
			if (!parent) return nullptr;
			Node* sibling;

			if (parent->left != this) sibling = parent->left;
			else sibling = parent->right;

			if (!(sibling->data)) throw 1;
			return sibling->left;

		}

		Node* Parent() {
			return parent;
		}

		int black_heingt() {
			Node* node = this;
			if (!(node->data)) return 0;
			if (node->color == Color::Black) {
				return 1 + max(node->left->black_heingt(), node->left->black_heingt());
			}
			else if (node->color == Color::Red) {
				return 0 + max(node->left->black_heingt(), node->left->black_heingt());
			}
		}

		bool InCorrectBalanceNode() {
			if (!data) return true;
			int right_h = this->right->black_heingt();
			int left_h = this->left->black_heingt();
			return ((right_h == left_h) && this->right->InCorrectBalanceNode() && this->left->InCorrectBalanceNode());
		}


	};

	Node* root;


	
	void rotateLeft(Node* x) {
		Node* y = x->right;
		Node* _parent = x->parent;
		x->right = y->left;

		if (y->left) y->left->parent = x;

		if (_parent) {
			if (_parent->left == x) _parent->left = y;
			else _parent->right = y;
		}

		y->parent = x->parent;

		x->parent = y;
		y->left = x;
		if (!(y->parent)) root = y;
	}

	void rotateRight(Node* x) {
		Node* y = x->left;
		Node* _parent = x->parent;
		x->left = y->right;

		if (x->left) x->left->parent = x;

		if (_parent) {  // зачем? родитель x не может быть nullptr
			if (_parent->left == x) _parent->left = y;
			else _parent->right = y;
		}

		y->parent = x->parent;

		x->parent = y;
		y->right = x;
		if (!(y->parent)) root = y;
	}

	Node* NodeFind(string key, Node* node=nullptr) {
		Node* tmp;
		if (!node) tmp = root;
		else tmp = node;  // необязательно continue ставить?
		if (!tmp) return nullptr;
		while (tmp->data) {
			if (key < tmp->key) {
				tmp = tmp->left;
				continue;
			}
			if (key > tmp->key) {
				tmp = tmp->right;
				continue;
			}
			if (key == tmp->key) {
				return tmp;
			}
		}
		return tmp;
	}

	void balanceInsert(Node* x) {
		if (!(x->parent)) { x->color = Color::Black; return; }
		if (x->parent->color == Color::Black) { return; }
		Node* parent = x->Parent();
		Node* grandparent = x->Grandparent();
		Node* uncle = x->Uncle();
		
		if (uncle->color == Color::Red) {
			parent->color = Color::Black;
			uncle->color = Color::Black;
			grandparent->color = Color::Red;
			balanceInsert(grandparent);
			return;
		}

		else if (uncle->color == Color::Black) {
			if (grandparent->left == parent) {
				if (x == parent->right) {
					rotateLeft(parent);
					x = parent;
				}
				x->Parent()->color = Color::Black;
				x->Grandparent()->color = Color::Red;
				rotateRight(x->Grandparent());
			}

			else if (grandparent->right == parent) {
				if (x == parent->left) {
					rotateRight(parent);
					x = parent;
				}
				x->Parent()->color = Color::Black;
				x->Grandparent()->color = Color::Red;
				rotateLeft(x->Grandparent());
			}
		}
	}

	void balanceDelete(Node* x) {
		if (!(x->parent)) return;

		Node* sibling;

		if (x->parent->left != x) sibling = x->parent->left;
		else sibling = x->parent->right;

		Node* parent = x->parent;
		Node* Rsibling = sibling->right;
		Node* Lsibling = sibling->left;

		if (sibling->color==Color::Red) {
			parent->color = Color::Red;
			sibling->color = Color::Black;
			if (parent->left == x) rotateLeft(parent);
			else rotateRight(parent);
		}
		if (parent->color == Color::Black && sibling->color == Color::Black && Rsibling->color == Color::Black &&
			Lsibling->color == Color::Black) {
			sibling->color = Color::Red;
			balanceDelete(parent);
			return;
		}

		if (x->Parent()->color == Color::Red && x->Sibling()->color == Color::Black && x->RSibling()->color == Color::Black &&
			x->LSibling()->color == Color::Black) {
			x->Sibling()->color = Color::Red;
			x->Parent()->color = Color::Black;
			return;
		}

		if (x->Parent()->left == x) {
			if ((x->LSibling()->color == Color::Red) && (x->RSibling()->color == Color::Black)) {
				x->Sibling()->color = Color::Red;
				x->LSibling()->color = Color::Black;
				rotateRight(x->Sibling());
			}
			x->Sibling()->color = parent->color;
			x->Parent()->color = Color::Black;
			x->RSibling()->color = Color::Black;
			rotateLeft(parent);
			return;
		}

		else if (x->Parent()->right == x) {
			if ((x->LSibling()->color == Color::Black) && (x->RSibling()->color == Color::Red)) {
				x->Sibling()->color = Color::Red;
				x->RSibling()->color = Color::Black;
				rotateLeft(x->Sibling());
			}
			x->Sibling()->color = parent->color;
			x->Parent()->color = Color::Black;
			x->LSibling()->color = Color::Black;
			rotateRight(parent);
			return;
		}


	}

public:
	// конструктор, диструктор, оператор=, копирования

	~RedBlackTree() {
		delete root;
	}

	int sizeNode(Node* node) {
		if (!node->data) return 0;
		return 1 + sizeNode(node->right) + sizeNode(node->left);
	}

	int size() {
		if (!root) return 0;
		return sizeNode(root);
	}

	bool InCorrectBalanceTree() {
		if (!root) return true;
		root->InCorrectBalanceNode();
	}


	RedBlackTree() { root = nullptr; }

	RedBlackTree(const RedBlackTree& other) {
		if (!other.root) {
			root = other.root;
			return;
		}
		root = nullptr;

		std::vector<Node*> remaining;
		Node* cur = other.root;
		while (cur) {
			if (cur->data) Insert(cur->key, *(cur->data));
			if (cur->right->data) {
				remaining.push_back(cur->right);
			}
			if (cur->left->data) {
				cur = cur->left;
			}
			else if (remaining.empty()) {
				break;
			}
			else {
				cur = remaining.back();
				remaining.pop_back();
			}
		}
	}


	Polinom* Find(string key) {
		Node * node = NodeFind(key);
		if (!node) return nullptr;
		return node->data;
	}

	bool Insert(string key, Polinom value) {
		Node* nil = NodeFind(key);
		if (!nil) {
			nil = root = new Node;
			nil->parent = nullptr;
		}
		else if (nil->data) return false;
		nil->key = key;
		nil->data = new Polinom(value);  // используется конструктор копирования по умолчанию
		nil->color = Color::Red;
		nil->left = new Node;
		nil->left->parent = nil;
		nil->right = new Node;
		nil->right->parent = nil;
		balanceInsert(nil);
		return true;
	}


	void print() {
		if (root) _print(0, root);
		cout << "\n";
	}

	void _print(int deep, Node* p)
	{
		if (p->data)
		{
			_print(deep + 1, p->right);
			for (int i = 0; i < deep; i++)
				cout << "  ";
			if (p->color == Color::Black) cout << "B";
			else cout << "R";
			cout << p->key << endl;
			_print(deep + 1, p->left);
		}
	}

	bool Delete(string key) {
		Node* z = NodeFind(key);
		if (!z) return false; // if empty
		if (!z->data) return false;  // if not NodeFind
		Node* y = NodeFind(key, z->left)->parent;// нашли максимальный элемент в левом поддереве
		//if (!(y->parent)) {   // когда удаляем просто корень
		//	if (!(y->right->data)) {
		//		root->key = y->right;
		//		root->parent = nullptr;
		//	}
		//	delete y;
		//	root = nullptr;
		//	return true;
		//}
		Polinom* tmp = z->data;
		z->data = y->data;
		y->data = tmp;
		z->key = y->key;

		if (y->color == Color::Red) {
			if (y->parent->left == y) {
				y->parent->left = new Node;
				y->parent->left->parent = y->parent;
			}
			if (y->parent->right == y) {
				y->parent->right = new Node;
				y->parent->right->parent = y->parent;
			}
			delete y;
			return true;
		}

		// остался случай когда у - чёрный

		if (y->right->color == Color::Red) {  // когда нашли сами себя и есть правый ребёнок
			Polinom* tmp = y->data;
			y->data = y->right->data;
			y->key = y->right->key;
			y->right->data = tmp;
			delete y->right;
			y->right = new Node;
			y->right->parent = y;
			return true;
		}

		if (!y->left->data) { // когда у не имеет детей
			if (!y->parent) {  // y - корень
				delete y;
				root = nullptr;
				return true;
			}
			balanceDelete(y);
			if (y->parent->left == y) {
				y->parent->left = new Node;
				y->parent->left->parent = y->parent;
			}
			else if (y->parent->right == y) {
				y->parent->right = new Node;
				y->parent->right->parent = y->parent;
			}
			delete y;
		}

		else if (y->left->color == Color::Red) {
			Polinom* tmp = y->data;
			y->data = y->left->data;
			y->key = y->left->key;
			y->left->data = tmp;
			delete y->left;
			y->left = new Node;
			y->left->parent = y;
		}

		return true;
	}

	bool Empty() {
		if (!root) return true;

	}
};
