#include <map>
#include <string>
#include <vector>
#include "List.h"

class Polinom {
	int size;
	List<pair<int, double>> data;

	vector<string> polinom;           // Double числа + все остальное		
	void Parse(string pol);           // Парсинг выражения: Строка -> Лексемы
	bool LexicalCheck(string number); // Лексический анализ
	bool SyntaxCheck();               // Проверка на соответствие языку 

	  
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
