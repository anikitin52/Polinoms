#include <map>
#include <string>
#include <vector>
#include "List.h"

class Polinom {
	int size;
	List<pair<int, double>> data;

	vector<string> polinom;           // Double ����� + ��� ���������		
	void Parse(string pol);           // ������� ���������: ������ -> �������
	bool LexicalCheck(string number); // ����������� ������
	bool SyntaxCheck();               // �������� �� ������������ ����� 

	  
public:
	Polinom();
	Polinom(string pol);
	void print();
	List<pair<int, double>> get_data();
	Polinom& operator+(Polinom pol);
	Polinom& operator-(Polinom pol);
	Polinom& operator*(double c);
	Polinom operator*(Polinom pol);
	Polinom& operator/(double c);
};
