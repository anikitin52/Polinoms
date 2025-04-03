#include "SortedTable.h"


void SortedTable::Insert(string key, Polinom value)
{
	if (Find(key)) throw "Key is already exists"; // Ïðîâåðêà íà íàëè÷èå êëþ÷à
	int size = data.size();
	int min = 0, max = size - 1;
	int posToInsert = size; // Ïî óìîë÷àíèþ âñòàâëÿåì â êîíåö

	// Áèíàðíûé ïîèñê ïîçèöèè äëÿ âñòàâêè 
	while (min <= max) {
		int midle = min + (max - min) / 2;
		if (data[midle].key < key) min = midle + 1;
		else {
			max = midle - 1;
			posToInsert = midle;
		}
	}

	// Âñòàâêà â íóæíóþ ïîçèöèþ
	data.insert(data.begin() + posToInsert, TableLine(key, value));

}

void SortedTable::Delete(string key)
{
	Polinom* ptrToDel = Find(key); // Ïîñèê óêàçàòåëÿ íà óäàëÿåìûé ýëåìåíò
	if (!ptrToDel) throw "No Element!"; // Ïðîâåðêà ñóùåñòâîâàíèÿ ýëåìåíòà
	bool findElem = false;
	for (int i = 0; i < data.size()-1; i++) {
		if (&data[i].value == ptrToDel) {
			findElem = true;
		}
		if (findElem == true) {
			swap(data[i], data[i + 1]);
		}
	}
	data.pop_back();
	/*
	vector<TableLine> newdata; 
	for (auto& el : data) {
		if (&el.value != ptrToDel) {
			newdata.push_back(el);
		}
	}
	this->data = newdata; // Ïåðåçàïèñü äâííûõ
	*/
	// без доп вектора двигаем в конец
}

Polinom* SortedTable::Find(string key)
{
	// Áèíàðíûé ïîèñê
	int size = data.size();
	int min = 0, max = size - 1;
	while (min <= max) {
		int midle = min + (max - min) / 2;
		if (data[midle].key == key) {
			return &data[midle].value; // Êëþ÷ íàéäåí
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
