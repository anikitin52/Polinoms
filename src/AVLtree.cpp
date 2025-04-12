#include "AVLtree.h"

AVLtree::Node* AVLtree::insert(Node* curr, const string& key, const Polinom& value)
{
    if (!curr) {
        return new Node(Element(key, value));
    }

    if (key < curr->data.key) {
        curr->left = insert(curr->left, key, value);
    }
    else if (key > curr->data.key) {
        curr->right = insert(curr->right, key, value);
    }
    else {
        curr->data.value = value;
    }

    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    return balance(curr);
}

AVLtree::Node* AVLtree::remove(Node* curr, const string& key)
{
    if (!curr) {
        return nullptr;
    }

    if (key < curr->data.key) {
        curr->left = remove(curr->left, key);
    }
    else if (key > curr->data.key) {
        curr->right = remove(curr->right, key);
    }
    else {
        if (!curr->left || !curr->right) {
            Node* temp = curr->left ? curr->left : curr->right;

            if (!temp) {
                temp = curr;
                curr = nullptr;
            }
            else {
                *curr = *temp;
            }

            delete temp;
        }
        else {
            Node* temp = findMinNode(curr->right);
            curr->data = temp->data;
            curr->right = remove(curr->right, temp->data.key);
        }
    }

    if (!curr) {
        return nullptr;
    }

    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    return balance(curr);
}

AVLtree::Node* AVLtree::balance(Node* curr)
{
    int bf = BalanceFactor(curr);

    if (bf > 1 && BalanceFactor(curr->left) >= 0) {
        return rotateRight(curr);
    }
    else if (bf > 1 && BalanceFactor(curr->left) < 0) {
        curr->left = rotateLeft(curr->left);
        return rotateRight(curr);
    }
    else if (bf < -1 && BalanceFactor(curr->right) <= 0) {
        return rotateLeft(curr);
    }
    else if (bf < -1 && BalanceFactor(curr->right) > 0) {
        curr->right = rotateRight(curr->right);
        return rotateLeft(curr);
    }

    return curr;
}

AVLtree::Node* AVLtree::rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLtree::Node* AVLtree::rotateRight(Node* x)
{
    Node* y = x->left;
    Node* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int AVLtree::getHeight(Node* N)
{
    if (N == nullptr) {
        return 0;
    }
    return N->height;
}

int AVLtree::BalanceFactor(Node* N)
{
    return getHeight(N->right) - getHeight(N->left);
}

AVLtree::Node* AVLtree::findMinNode(Node* node)
{
    while (node->left) {
        node = node->left;
    }
    return node;
}

void AVLtree::clear(Node* node)
{
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

AVLtree::Node* AVLtree::clone(Node* node)
{
    if (node == nullptr) {
        return nullptr;
    }
    return new Node(node->data, clone(node->left), clone(node->right), node->height);
}



AVLtree::AVLtree(const AVLtree& other)
{
    root = clone(other.root);
}

AVLtree& AVLtree::operator=(const AVLtree& tr)
{
    if (this != &tr) {
        clear(root);
        root = clone(tr.root);
    }
    return *this;
}

AVLtree::~AVLtree()
{
    clear(root);
    root = nullptr;
}

AVLtree::Node* AVLtree::Insert(string key, Polinom value)
{
    if (!Find(key)) throw "Неуникальный ключ";
    return insert(root, key, value);
}

AVLtree::Node* AVLtree::Delete(string key)
{
	return remove(root, key);
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
