#include <iostream>
#include <string>
#include "Polinom.h"
#include "HashTableC.h"
#include "DirectHashTable.h"
#include "Tablice.h"
#include "SortedTable.h"
#include "AVLtree.h"
#include "RedBlackTree.h"
#include <fstream>
#include <string>

class DataBase {
    Table database1;
    SortedTable database2;
    AVLtree database3;
    RedBlackTree database4;
    HashTable database5 = HashTable(100);
    DirectHashTable<100> database6;
    int marker;
public:
    DataBase(int _marker) : marker(_marker) {}
    void Insert(string key, Polinom p) {
        switch (marker) {
        case 1: {
            database1.Insert(key, p);
        }
        case 2: {
            database2.Insert(key, p);
        }
        case 3: {
            database3.Insert(key, p);
        }
        case 4: {
            database4.Insert(key, p);
        }
        case 5: {
            database5.Insert(key, p);
        }
        case 6: {
            database6.Insert(key, p);
        }
        }
    }

    Polinom* Find(string key) {
        switch (marker) {
        case 1: {
            return database1.Find(key);
        }
        case 2: {
            return database2.Find(key);
        }
        case 3: {
            return database3.Find(key);
        }
        case 4: {
            return database4.Find(key);
        }
        case 5: {
            //return database5.Find(key);
        }
        case 6: {
            return database6.Find(key);
        }
        }
    }


    void Delete(string key) {
        switch (marker) {
        case 1: {
            database1.Delete(key);
        }
        case 2: {
            database2.Delete(key);
        }
        case 3: {
            database3.Delete(key);
        }
        case 4: {
            database4.Delete(key);
        }
        case 5: {
            database5.Delete(key);
        }
        case 6: {
            database6.Delete(key);
        }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Добро пожаловать в базу данных для хранения полиномов!" << endl;
    cout << "Введите цифру: структуру данных, на которой будет осуществляться хранение." << endl;
    cout << "Доступные структуры хранения: 1 - неупорядоченная таблица, 2 - упорядоченная таблица" << endl;
    cout << "Доступные структуры хранения: 3 - AVL-дерево, 4 - красно-чёрное дерево" << endl;
    cout << "Доступные структуры хранения: 5 - хэш-таблица методом цепочек, 6 - хэш-таблица методом открытой адресации" << endl;
    std::string input;

    while (true) {
        std::getline(std::cin, input);
        if (input == "1") {
            std::cout << "Вы выбрали неупорядоченную таблицу." << std::endl;
            break;
        }
        if (input == "2") {
            std::cout << "Вы выбрали неупорядоченную таблицу." << std::endl;
            break;
        }
        if (input == "3") {
            std::cout << "Вы выбрали AVL-дерево." << std::endl;
            break;
        }
        if (input == "4") {
            std::cout << "Вы выбрали красно-чёрное дерево." << std::endl;
            break;
        }
        if (input == "5") {
            std::cout << "Вы выбрали хэш-таблицу методом цепочек." << std::endl;
            break;
        }
        if (input == "6") {
            std::cout << "Вы выбрали хэш-таблицу методом открытой адресации" << std::endl;
            break;
        }
        cout << "Введите цифру: структуру данных, на которой будет осуществляться хранение." << endl;
        cout << "Доступные структуры хранения: 1 - неупорядоченная таблица, 2 - упорядоченная таблица" << endl;
        cout << "Доступные структуры хранения: 3 - AVL-дерево, 4 - красно-чёрное дерево" << endl;
        cout << "Доступные структуры хранения: 5 - хэш-таблица методом цепочек, 6 - хэш-таблица методом открытой адресации" << endl;
    }

    DataBase database(stoi(input));


	std::string line;
	std::ifstream in("TextFile1.txt");
    //заполняем database
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            //size_t space_pos = line.find(' ');
            //string key = line.substr(0, space_pos);
            //string str_value = line.substr(space_pos + 1);
            //Polinom value = Polinom(str_value);
            //cout << key << " ";
            //cout << str_value << endl;
            database.Insert(line, Polinom(line));
        }
    }
    in.close();


    while (true) {
        cout << "Введите тип совершаемой операции: 1 - вставка, 2 - удаление, 3 - поиск" << endl;
        cout << "Введите 0 для выхода из приложения" << endl;
        std::getline(std::cin, input);
        if (input == "0") {
            std::cout << "Вы ввели '0'. Программа завершает работу." << std::endl;
            break;
        }
        if (input == "1") {
            std::cout << "Введите ключ вставляемого элемента:" << std::endl;
            std::getline(std::cin, input);
            string key = input;
            std::cout << "Введите значение вставляемого элемента:" << std::endl;
            std::getline(std::cin, input);
            Polinom value = Polinom(input);
            database.Insert(key, value);
        }
        if (input == "2") {
            std::cout << "Введите ключ удаляемого элемента:" << std::endl;
            std::getline(std::cin, input);
            database.Delete(input);
        }
        if (input == "3") {
            std::cout << "Введите ключ искомого элемента:" << std::endl;
            std::getline(std::cin, input);
            string key = input;
            Polinom* p = database.Find(key);
            if (!p) {
                std::cout << "Элемент с таким ключом не найден." << std::endl;
            }
            else {
                std::cout << "Элемент с таким ключом найден. " << std::endl;
                std::cout << "Возвращаемое значение: " << *p << endl;
            }
        }
    }
    return 0;
}


