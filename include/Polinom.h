// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>



using namespace std;   // лучше так не делать


class Polinom {
	template<class T>
	class Stack
	{
		vector<T> data;
		int top;
	public:
		Stack() : top(-1) {}
		size_t size() const { return top + 1; }
		bool IsEmpty() const { return top == -1; }
		void Push(const T& val) {
			data.push_back(val);
			top++;
		}
		T Pop() {
			if (IsEmpty()) throw 1;
			T value = data[top]; // получаем значение последнего элемента
			data.pop_back();
			top--;
			return value;
		}
	};
	int Parse(string __str);
	int status; // = 1 если исходная строка корректна
	vector<pair<unsigned int, double>> monoms;
public:
	Polinom(string src_str) {
		int result = Parse(src_str);  // Parse() заполянет поле status в зависимости от корректности строки
		if ((result < 0) || (result > 0)) {
			status = 0;
			cout << "error code : " << result << endl;
		}
		else {
			sort(monoms.rbegin(), monoms.rend());  // нужен ли отдельный тест?
			cout << "that's all right!" << endl;
		}
	}

	Polinom(vector<pair<unsigned int, double>> _monoms, int notsort = 0) {
		for (int i = 0; i < _monoms.size(); i++) {
			if (_monoms[i].second != 0) {
				if (_monoms[i].second >= (unsigned int)1000) { throw 1; }  // нужно ли явное приведение типов?
				monoms.push_back(_monoms[i]);
			}
		}
		if (!notsort) {
			sort(monoms.rbegin(), monoms.rend());
		}
		status = 1;
	}
	int GetStatus() const { return status; }
	double Calculate(vector<double> values);
	Polinom operator+(const Polinom &other) const{  // зачем &?
		if (GetStatus() == 0) {
			throw 1;
		}
		if (other.GetStatus() == 0) {
			throw 1;
		}
		vector<pair<unsigned int, double>> res_vector;
		// лучше friend функция?
		int i = 0, j = 0, k = 0;
		int n1 = monoms.size();
		int n2 = other.monoms.size();
		while (i < n1 && j < n2) {
			if (monoms[i].first > other.monoms[j].first) {
				res_vector.push_back(monoms[i++]);
			}
			if (monoms[i].first < other.monoms[j].first) {
				res_vector.push_back(other.monoms[j++]);
			}
			if (monoms[i].first == other.monoms[j].first) {
				if ((other.monoms[j].second + monoms[i].second) != 0) {
					pair<int, double> p = { monoms[i].first, other.monoms[j].second + monoms[i].second };
					res_vector.push_back(p);
				}
				i++; j++;
			}
		}
		while (i < n1) {
			res_vector.push_back(monoms[i++]);
		}
		while (j < n2) {
			res_vector.push_back(other.monoms[j++]);
		}
		return Polinom(res_vector);
	}

	Polinom operator*(const double value) const {
		if (GetStatus() == 0) {
			throw 1;
		}
		vector<pair<unsigned int, double>> res_vector;
		if (value == 0.0) {
			return Polinom(res_vector);  // на случай если передали ноль
		}
		for (int i = 0; i < monoms.size(); i++) {
			pair<int, double> p = { monoms[i].first, monoms[i].second * value};
			res_vector.push_back(p);
		}
		return Polinom(res_vector);
	}

	Polinom operator-(const Polinom& other) {
		return *this + (other*(-1));
	}

	Polinom operator*(const Polinom& other) const {
		if (GetStatus() == 0) {
			throw 1;
		}
		if (other.GetStatus() == 0) {
			throw 1;
		}

		vector<pair<unsigned int, double>> res_vect;
		Polinom p_res(res_vect);
		for (int i = 0; i < monoms.size(); i++) {
			vector<pair<unsigned int, double>> res_vector;
			for (int j = 0; j < other.monoms.size(); j++) {
				double koef = monoms[i].first + other.monoms[j].first;
				if (koef > 999) {
					throw 1;
				}
				pair<int, double> p = { koef, monoms[i].second * other.monoms[j].second };
				res_vector.push_back(p);
			}
			Polinom p_tmp(res_vector, 1);
			p_res = p_res + p_tmp; // передача 1 отменяет сортировку при создании полинома
		}
		return p_res;
	}

	friend ostream& operator<<(ostream& ostr, const Polinom& pol)
	{
		if (pol.GetStatus() == 0) {
			throw 1;
		}
		string str = "";
		for (int i = 0; i < pol.monoms.size(); i++) {
			if (i > 0) str += '+';
			str += to_string(pol.monoms[i].second) + "x^" + to_string(pol.monoms[i].first / 100);
			str += "y^" + to_string(pol.monoms[i].first % 100 / 10);
			str += "z^" + to_string(pol.monoms[i].first % 10);
		}
		ostr << str;
		return ostr;
	}

	bool operator==(const Polinom & other) const {
		if (other.GetStatus() == 0) {
			throw 1;
		}
		if (this->GetStatus() == 0) {
			throw 1;
		}
		if (other.monoms.size() != monoms.size()) {
			return false;
		}
		for (int i = 0; i < monoms.size(); i++) {
			if (monoms[i] != other.monoms[i]) return false;
		}
		return true;
	}

	bool operator!=(const Polinom& other) const noexcept {
		return !(*this == other);
	}
};

//class Translator {
//	template<class T>
//	class Stack
//	{
//		vector<T> data;
//		int top;
//	public:
//		Stack() : top(-1) {}
//		size_t size() const { return top + 1; }
//		bool IsEmpty() const { return top == -1; }
//		void Push(const T& val) {
//			data.push_back(val);
//			top++;
//		}
//		T Pop() {
//			if (IsEmpty()) throw 1;
//			T value = data[top]; // получаем значение последнего элемента
//			data.pop_back();
//			top--;
//			return value;
//		}
//	};
//	enum class name_term {function, variable, number, brecket};
//	struct Term{
//		Term(name_term _name) : name(_name) {}
//		name_term GetNameTerm() {
//			return name;
//		}
//		virtual ~Term() {}
//
//	protected:
//		name_term name;  // верно ли?
//	};
//	struct Brecket : public Term {
//	protected:
//		char brecket_type;
//	public:
//		char GetBracketType() { return brecket_type; } const
//		Brecket(char str1) : Term(name_term::brecket), brecket_type(str1) {};
//	};
//	struct Var: public Term {
//	protected:
//		string name_var;    // нужно ли вводить секцию protected?
//		map<string, double>& map_operands;
//	public:
//		Var(string _name_var, map<string, double>& map_operands): Term(name_term::variable),
//			name_var(_name_var), map_operands(map_operands) {};
//		string GetNameVar() { return name_var; }
//		double GetValue() { return map_operands[name_var]; }
//
//	};
//	struct Number : public Term {
//	protected:
//		double value;
//	public:
//		Number(double _value): Term(name_term::number), value(_value) {}
//		double GetValue() { return value; }
//	};
//	struct Function : public Term {
//	protected:
//		string name_func;
//		int is_bin;
//	public:
//		Function(string _name_func, int _is_bin=1): Term(name_term::function), name_func(_name_func), is_bin(_is_bin) {}  // сработает?
//		string GetName() { return name_func; }
//		int GetIsBin() { return is_bin; }
//		void ChangeIsBin(int _is_bin) { is_bin = _is_bin; }
//		double function(double const arg1, double const arg2=0) {
//			if (name_func == "abs") return abs(arg1);
//			if (name_func == "sin") return sin(arg1);
//			if (name_func == "cos") return cos(arg1);
//			if (name_func == "tg") return tan(arg1);
//			if (name_func == "^") return pow(arg1, arg2);
//			if (name_func == "+") {
//				if (GetIsBin()) return arg1 + arg2;  // унарные + и - тоже учитываются
//				else return arg1;
//			}
//			if (name_func == "-") {
//				if (GetIsBin()) return arg1 - arg2;
//				else return -arg1;
//			}
//			if (name_func == "*") return arg1 * arg2;
//			if (name_func == "/") {
//				if (arg2 == 0) throw 1;
//				else return arg1 / arg2;
//		}
//		}
//	};
//	string src_str;  // исходная строка
//	vector<Term*> infix;
//	vector<Term*> postfix;
//	map<string, double> operands;
//	void ToPostfix();
//	int Parse();
//	int LexemParse();
//	int SyntaxParce();
//	int status; // = 1 если исходная строка корректна
//public:
//	int GetStatus() { return status; }
//	Translator(string _str) : src_str(_str) {
//		int result = Parse();  // Parse() заполянет поле status в заивисимости от корректности строки
//		if ((result < 0) || (result > 0)) {
//			status = 0;
//			cout << "Error code : " << result << endl;
//		}
//		else { cout << "That's all right!" << endl; status = 1; }
//	}
//	vector<string> GetOperands() const {
//		vector<string> op;
//		for (const auto& item : operands)
//			if (!item.second) { op.push_back(item.first); }  // проверяем,не явялется ли значение уже установленным (то есть в случае математической константы)
//		return op;
//	}
//	double Calculate(const map<string, double>& values);
//};

#endif