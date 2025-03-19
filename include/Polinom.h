#include <string>
#include <vector>
#include <algorithm>
#include "List.h"

class Polinom {
	int size;
	vector<pair<int, double>> data;

	vector<string> polinom;           // Double ����� + ��� ���������		
	void Parse(string pol);           // ������� ���������: ������ -> �������
	bool LexicalCheck(string number); // ����������� ������
	bool SyntaxCheck();               // �������� �� ������������ ����� 
	void SortData();

	  
public:
	Polinom();
	Polinom(string pol);
	void print();
	void printPair();
	const std::vector<std::pair<int, double>>& get_data() const { return data; }
	Polinom operator+(const Polinom& other) const;
	Polinom operator-(const Polinom& other) const;
	Polinom& operator*(double c);
	Polinom operator*(const Polinom& other) const;;
	Polinom& operator/(double c);
};
