#include "SortedTable.h"


void SortedTable::Insert(string key, Polinom value)
{
	if (Find(key)) throw "Key is already exists"; // Проверка на наличие ключа
	int size = data.size();
	int min = 0, max = size - 1;
	int posToInsert = size; // По умолчанию вставляем в конец

	// Бинарный поиск позиции для вставки 
	while (min <= max) {
		int midle = min + (max - min) / 2;
		if (data[midle].key < key) min = midle + 1;
		else {
			max = midle - 1;
			posToInsert = midle;
		}
	}

	// Вставка в нужную позицию
	data.insert(data.begin() + posToInsert, TableLine(key, value));

}

void SortedTable::Delete(string key)
{
	Polinom* ptrToDel = Find(key); // Посик указателя на удаляемый элемент
	if (!ptrToDel) throw "No Element!"; // Проверка существования элемента
	vector<TableLine> newdata; 
	for (auto& el : data) {
		if (&el.value != ptrToDel) {
			newdata.push_back(el);
		}
	}
	this->data = newdata; // Перезапись двнных
}

Polinom* SortedTable::Find(string key)
{
	// Бинарный поиск
	int size = data.size();
	int min = 0, max = size - 1;
	while (min <= max) {
		int midle = min + (max - min) / 2;
		if (data[midle].key == key) {
			return &data[midle].value; // Ключ найден
		}
		if (data[midle].key < key) {
			min = midle + 1;
		}
		else {
			max = midle - 1;
		}
	}
	return nullptr;
}
