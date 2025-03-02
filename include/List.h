#include <iostream>

using namespace std;

template<typename T>
class List
{
    struct Node
    {
        T data;
        Node* next;
        Node(T data, Node* next) : data(data), next(next) {}
    };
    Node* first;

public:

    List() {
        first = nullptr;
    }

    List(int n) {
        if (n < 0) {
            throw "Error!";
        }
        if (n == 0) {
            first = nullptr;
            return;
        }
        first = new Node(T(), nullptr);
        Node* current = first;
        for (int i = 1; i < n; i++) {
            Node* tmp = new Node(T(), nullptr);
            current->next = tmp;
            current = current->next;
        }
    }

    List(const List& other) {
        if (!other.first) {
            first = nullptr;
            return;
        }
        first = new Node(other.first->data, nullptr);
        Node* current = first;
        Node* ocurrent = other.first->next;
        while (ocurrent) {
            current->next = new Node(ocurrent->data, nullptr);
            current = current->next;
            ocurrent = ocurrent->next;
        }
    }

    ~List() {
        while (first) {
            Node* second = first->next;
            delete first;
            first = second;
        }
    }

    List(int n, T dflt) {
        if (n < 0) {
            throw "Error!";
        }
        if (n == 0) {
            first = nullptr;
            return;
        }
        first = new Node(dflt, nullptr);
        Node* current = first;
        for (int i = 1; i < n; i++) {
            Node* tmp = new Node(dflt, nullptr);
            current->next = tmp;
            current = current->next;
        }
    }

    List& operator=(const List& l) {
        if (this == &l) {
            return *this;
        }
        while (first) {
            Node* second = first->next;
            delete first;
            first = second;
        }
        if (!l.first) {
            first = nullptr;
            return *this;
        }
        first = new Node(l.first->data, nullptr);
        Node* current = first;
        Node* ocurrent = l.first->next;
        while (ocurrent) {
            current->next = new Node(ocurrent->data, nullptr);
            current = current->next;
            ocurrent = ocurrent->next;
        }
        return *this;
    }


    T& operator[] (int index) {
        if (index < 0) {
            throw "Error!";
        }
        Node* current = first;
        for (int i = 0; i < index; i++) {
            if (current == nullptr) {
                throw "Error!";
            }
            current = current->next;
        }
        if (current == nullptr) {
            throw "Error!";
        }
        return current->data;
    }

    Node* insert(T value, Node* prev) {
        if (prev == nullptr) {
            throw "Error!";
        }
        Node* tmp = new Node(value, prev->next);
        prev->next = tmp;
        return tmp;
    }

    Node* erase(Node* prev) {
        if (prev == nullptr) {
            throw "Error!";
        }
        Node* tmp = prev->next;
        if (!prev->next) throw "Error!";
        prev->next = tmp->next;
        delete tmp;
        return prev->next;

    }

    Node* find(T value) {
        Node* current = first;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    size_t size() {
        int size = 0;
        Node* current = first;
        while (current) {
            size += 1;
            current = current->next;
        }
        return size;
    }

    /*
  Task 4
  Find the middle item in the list in one pass.
  If the number of items in the list is even, find the two middle items.
  Time: O(n), 1 pass
  Memory: O(1)
  */

    T* midle_element() {
        Node* current = first;
        Node* current2 = first;
        if (current->next == nullptr) {
            T res[1] = { current->data };
            return res;
        }
        if (current->next->next == nullptr) {
            T res[2] = { current->data, current->next->data };
            return res;
        }
        while (current->next != nullptr && current->next->next != nullptr) {
            current = current->next;
            current = current->next;
            current2 = current2->next;
        }
        T res[2] = { current2->data, current2->next->data };
        return res;
    }

    void print() {
        Node* current = first;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
    }

    void push_back(T data) {
        Node* current = first;
        if (!first) {
            first = new Node(data, nullptr);
            return;
        }
        while (current->next) {
            current = current->next;
        }
        current->next = new Node(data, nullptr);
    }

    class iterator {
        Node* cur;
        friend List;
        explicit iterator(Node* node) : cur(node) {}
    public:
        iterator& operator++() {
            cur = cur->next;
            return *this;
        }
        iterator operator++(int) {
            iterator copy = *this;
            cur = cur->next;
            return copy;
        }
        T& operator*() {
            return cur->data;
        }
        T* operator->() {
            return &(cur->data);
        }
        friend bool operator!=(const iterator it1, const iterator it2) {
            return it1.cur != it2.cur;
        }

    };

    iterator begin() {
        return iterator(first);
    }
    iterator end() {
        return iterator(nullptr);
    }
};