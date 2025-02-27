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

using namespace std;   // лучше так не делать


class Translator {
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
	enum class name_term {function, variable, number, brecket};
	struct Term{
		Term(name_term _name) : name(_name) {}
		name_term GetNameTerm() {
			return name;
		}
		virtual ~Term() {}

	protected:
		name_term name;  // верно ли?
	};
	struct Brecket : public Term {
	protected:
		char brecket_type;
	public:
		char GetBracketType() { return brecket_type; } const
		Brecket(char str1) : Term(name_term::brecket), brecket_type(str1) {};
	};
	struct Var: public Term {
	protected:
		string name_var;    // нужно ли вводить секцию protected?
		map<string, double>& map_operands;
	public:
		Var(string _name_var, map<string, double>& map_operands): Term(name_term::variable),
			name_var(_name_var), map_operands(map_operands) {};
		string GetNameVar() { return name_var; }
		double GetValue() { return map_operands[name_var]; }

	};
	struct Number : public Term {
	protected:
		double value;
	public:
		Number(double _value): Term(name_term::number), value(_value) {}
		double GetValue() { return value; }
	};
	struct Function : public Term {
	protected:
		string name_func;
		int is_bin;
	public:
		Function(string _name_func, int _is_bin=1): Term(name_term::function), name_func(_name_func), is_bin(_is_bin) {}  // сработает?
		string GetName() { return name_func; }
		int GetIsBin() { return is_bin; }
		void ChangeIsBin(int _is_bin) { is_bin = _is_bin; }
		double function(double const arg1, double const arg2=0) {
			if (name_func == "abs") return abs(arg1);
			if (name_func == "sin") return sin(arg1);
			if (name_func == "cos") return cos(arg1);
			if (name_func == "tg") return tan(arg1);
			if (name_func == "^") return pow(arg1, arg2);
			if (name_func == "+") {
				if (GetIsBin()) return arg1 + arg2;  // унарные + и - тоже учитываются
				else return arg1;
			}
			if (name_func == "-") {
				if (GetIsBin()) return arg1 - arg2;
				else return -arg1;
			}
			if (name_func == "*") return arg1 * arg2;
			if (name_func == "/") {
				if (arg2 == 0) throw 1;
				else return arg1 / arg2;
		}
		}
	};
	string src_str;  // исходная строка
	vector<Term*> infix;
	vector<Term*> postfix;
	map<string, double> operands;
	void ToPostfix();
	int Parse();
	int LexemParse();
	int SyntaxParce();
	int status; // = 1 если исходная строка корректна
public:
	int GetStatus() { return status; }
	Translator(string _str) : src_str(_str) {
		int result = Parse();  // Parse() заполянет поле status в заивисимости от корректности строки
		if ((result < 0) || (result > 0)) {
			status = 0;
			cout << "Error code : " << result << endl;
		}
		else { cout << "That's all right!" << endl; status = 1; }
	}
	vector<string> GetOperands() const {
		vector<string> op;
		for (const auto& item : operands)
			if (!item.second) { op.push_back(item.first); }  // проверяем,не явялется ли значение уже установленным (то есть в случае математической константы)
		return op;
	}
	double Calculate(const map<string, double>& values);
};

#endif