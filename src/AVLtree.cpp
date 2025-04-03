#include "AVLtree.h"

AVLtree::~AVLtree()
{
}

AVLtree::Node* AVLtree::Insert(string key, Polinom value)
{
	return nullptr;
}

AVLtree::Node* AVLtree::Delete(string key)
{
	return nullptr;
}

Polinom* AVLtree::Find(string key)
{
	Node* current = root;

	while (current != nullptr) {
		if (key == current->data.key) {
			return &current->data.value;
		}
		else if (key < current->data.key) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return nullptr;
}

