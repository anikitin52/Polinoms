#include "SortedTable.h"

void SortedTable::Insert(string key, Polinom value)
{
	TableLine line(key, value);
	data.push_back(line);
	std::sort(data.begin(), data.end(),
		[](const TableLine& a, const TableLine& b) {
			return a.key < b.key; // Сортировка по возрастанию key
		});
}

void SortedTable::Delete(string key)
{
	vector<TableLine> tmp;
	for (auto el : data) {
		if (el.key != key) {
			tmp.push_back(el);
		}
		
	}
}

Polinom SortedTable::Find(string key)
{
	return Polinom("");
}
