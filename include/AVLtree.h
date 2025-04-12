#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"

class AVLtree {
private:
    struct Element {
        string key;
        Polinom value;

        Element(string _key, Polinom _value)
            : key(_key), value(_value) {}
    };

    struct Node {
        Element data;
        Node* left;
        Node* right;
        int height;

        Node(const Element& _data, Node* _left = nullptr, Node* _right = nullptr, int _height = 1)
            : data(_data), left(_left), right(_right), height(_height) {}
    };

    Node* root;
    

    Node* insert(Node* curr, const string& key, const Polinom& value);
    Node* remove(Node* curr, const string& key);
    
    Node* balance(Node* curr);
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* x);

    int getHeight(Node* N);
    int BalanceFactor(Node* N);
    Node* findMinNode(Node* node);
    void clear(Node* node);
    Node* clone(Node* node);

public:
    AVLtree() : root(nullptr) {}
    AVLtree(const AVLtree& other);
    AVLtree& operator=(const AVLtree& tr);
    ~AVLtree();

    Node* Insert(string key, Polinom value);
    Node* Delete(string key);
    Polinom* Find(string key);
};