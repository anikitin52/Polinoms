// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
#include <cstdlib>
#include "Polinom.h"
#include <algorithm>
#include <string>
#include <map>
#include <cmath>


int Polinom::Parse(string str) {
	status = 1;
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());  // probels?
	enum class Stat { Error, Sadd, Snumb0, Snumb1, Snumb2, Snumb3, Sdeg1, Sdeg2, Svar1, Svar2, Svar3, Svar1_, 
		Svar2_, Svar3_};
	Stat condition = Stat::Sadd;
	if (str[0] != '+' && str[0] != '-') {
		str = string(1, '+') + str;
	}
	pair<unsigned int, double> actual_pair;
	actual_pair.first = 0;
	actual_pair.second = 0;
	string actual_string = "";
	for (int i = 0; i < str.size(); i++) {
		switch (condition) {
		case Stat::Sadd:
			if (str[i] == '+' || str[i] == '-') { actual_string += str[i]; condition = Stat::Snumb0; break; }
			else condition = Stat::Error; break;
		case Stat::Snumb0:
			if (std::isdigit(str[i])) {
				actual_string += str[i]; condition = Stat::Snumb1; break;
			}
			if (str[i] == 'x') {
				actual_string += '1'; actual_pair.second = stod(actual_string);
				actual_string = ""; condition = Stat::Svar1_; break;
			}
			else { condition = Stat::Error; break; }
		case Stat::Snumb1:
			if (std::isdigit(str[i])) {
				actual_string += str[i]; condition = Stat::Snumb1; break;
			}
			if (str[i] == 'x') {
				actual_pair.second = stod(actual_string);
				actual_string = ""; condition = Stat::Svar1_; break;
			}
			if (str[i] == '.') { actual_string += str[i]; condition = Stat::Snumb2; break; }
			else condition = Stat::Error; break;
		case Stat::Snumb2:  // closed
			if (std::isdigit(str[i])) { actual_string += str[i]; condition = Stat::Snumb3; break; }
			else { condition = Stat::Error; break; }
		case Stat::Snumb3:
			if (std::isdigit(str[i])) {
				actual_string += str[i]; condition = Stat::Snumb3; break;
			}
			if (str[i] == 'x') {
				actual_pair.second = stod(actual_string);
				actual_string = ""; condition = Stat::Svar1_; break;
			}
			else { condition = Stat::Error; break; }
		case Stat::Svar1_:
			if (str[i] == '^') { condition = Stat::Svar1; break;}
			else { condition = Stat::Error; break; }
		case Stat::Svar1:
			if (std::isdigit(str[i])) {
				actual_pair.first += stoi(string(1, str[i])) * 100;  // стоит ли создавать для 100 константу?
				condition = Stat::Sdeg1; break;
			}
			else { condition = Stat::Error; break; }
		case Stat::Sdeg1:
			if (str[i] == 'y') {
				condition = Stat::Svar2_; break;
			}
			else { condition = Stat::Error; break; }
		case Stat::Svar2_:
			if (str[i] == '^') { condition = Stat::Svar2; break; }
			else { condition = Stat::Error; break; }
		case Stat::Svar2:
			if (std::isdigit(str[i])) {
				actual_pair.first += stoi(string(1, str[i])) * 10;  // стоит ли создавать для 10 константу?
				condition = Stat::Sdeg2;
				break;
			}
			else { condition = Stat::Error; break; }
		case Stat::Sdeg2:
			if (str[i] == 'z') {
				condition = Stat::Svar3_; break;
			}
			else { condition = Stat::Error; break; }
		case Stat::Svar3_:
			if (str[i] == '^') { condition = Stat::Svar3; break; }
			else { condition = Stat::Error; break; }
		case Stat::Svar3:
			if (std::isdigit(str[i])) {
				actual_pair.first += stoi(string(1, str[i])) * 1;
				if (actual_pair.second != 0.0) {
					monoms.push_back(actual_pair);  // проверяем что коэффициент не нулевой
				}
				actual_pair.first = 0;
				actual_pair.second = 0;
				condition = Stat::Sadd; break;
			}
			else { condition = Stat::Error; break; }
		// default: condition = Stat::Error; break;
		}
		if (condition == Stat::Error) { status = 0; return i + 1; }
	}
	if (condition != Stat::Sadd) {
		status = 0; return str.size();
	}
	return 0;
}


double Polinom::Calculate(vector<double> values) {
	if (status == 0) {
		throw 1;
	}
	if (values.size() != 3) {
		throw 1;
	}
	double value = 0.0;
	for (int i = 0; i < monoms.size(); i++) {
		double monom = monoms[i].second;
		int tmp = monoms[i].first;
		int ind = 2;
		while (tmp > 0) {
			monom *= pow(values[ind--], tmp % 10);
			tmp /= 10;
		}
		value += monom;
	}
	return value;
}


//int Translator::Parse() {
//	status = 1;
//	int result_parse = LexemParse();
//	if (result_parse > 0) {
//		status = 0;
//		return result_parse; 
//	} // вернёт номер символа, на котором прекратился лексич. анализ
//	result_parse = SyntaxParce();
//	if (result_parse < 0) {
//		status = 0;
//		return result_parse; // аналогично
//	}
//	return 0;
//}
//
//int Translator::LexemParse() {
//	// почему не удаётся использовать числовые константы из number
//	vector<string> control_func_bin = { "+", "-", "/", "*", "^"};
//	vector<string> control_func_unary = { "sin", "cos", "tg", "abs"};
//	vector<string> control_const = { "PI", "E" };
//	map<string, double> value_for_const{
//		{"PI", 3.141592653589793238463}, {"E", std::exp(1.0)}
//	};
//	enum class Stat{S0, Snumb1, Snumb2, Snumb3, Slit1, Error};
//	Stat condition = Stat::S0;
//	string actual_string = "";
//	int i = 0;
//	string str = src_str + ")"; // добавляем намеренно доп символ, в конце алгоритма удаляем
//	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
//	while(i<str.size()) {
//		switch(condition) {
//			case Stat::S0:  //closed
//				if (std::isdigit(str[i])) {
//					actual_string += str[i++]; condition = Stat::Snumb1; break;
//				}
//				if (std::isalpha(str[i])) { actual_string += str[i++]; condition = Stat::Slit1; break; };
//				if (find(control_func_bin.begin(), control_func_bin.end(), string(1, str[i])) != control_func_bin.end()) { // символ является операцией
//				/*	postfix.push_back(Number n(stod(actual_string)));*/
//					infix.push_back(static_cast<Term*>(new Function(string(1, str[i++]))));
//					actual_string = "";
//					condition = Stat::S0;
//					break;
//				}
//				if (str[i] == '(' || str[i] == ')') {
//					infix.push_back(static_cast<Term*>(new Brecket(str[i++])));
//					actual_string = "";
//					condition = Stat::S0;
//					break;
//				}
//				else condition = Stat::Error; break;
//			case Stat::Snumb1:  // closed
//				if (str[i] == '.') { actual_string += str[i++]; condition = Stat::Snumb2; break; }
//				if (std::isdigit(str[i])) { actual_string += str[i++]; condition = Stat::Snumb1; break; }
//				if (find(control_func_bin.begin(), control_func_bin.end(), string(1, str[i])) != control_func_bin.end()) { // символ является операцией
//					infix.push_back(static_cast<Term*>(new Number(stod(actual_string))));
//					infix.push_back(static_cast<Term*>(new Function(string(1, str[i++]))));
//					actual_string = "";
//					condition = Stat::S0;
//					break;
//				}
//				if (str[i] == ')') {  // closed
//					infix.push_back(static_cast<Term*>(new Number(stod(actual_string))));
//					infix.push_back(static_cast<Term*>(new Brecket(str[i++]))); actual_string = ""; condition = Stat::S0; break;
//				}
//				else { condition = Stat::Error; break; }
//			case Stat::Snumb2:  // closed
//				if (std::isdigit(str[i])) { actual_string += str[i++]; condition = Stat::Snumb3; break; }
//				else { condition = Stat::Error; break; }
//			case Stat::Snumb3:  // closed
//				if (std::isdigit(str[i])) { actual_string += str[i++]; break; }
//				if (find(control_func_bin.begin(), control_func_bin.end(), string(1, str[i])) != control_func_bin.end()) { // символ является операцией
//					infix.push_back(static_cast<Term*>(new Number(stod(actual_string))));
//					infix.push_back(static_cast<Term*>(new Function(string(1, str[i++]))));  // как добавить элемент в вектор указателей?
//					actual_string = "";
//					condition = Stat::S0;
//					break;
//				}
//				if (str[i] == ')') {  // closed
//					infix.push_back(static_cast<Term*>(new Number(stod(actual_string.c_str()))));
//					infix.push_back(static_cast<Term*>(new Brecket(str[i++]))); actual_string = ""; condition = Stat::S0; break;
//				}
//				else condition = Stat::Error; break;
//			case Stat::Slit1:
//				if (std::isalpha(str[i])) { actual_string += str[i++]; break; }
//				if (find(control_func_bin.begin(), control_func_bin.end(), string(1, str[i])) != control_func_bin.end()) {   // проверка что текущая строка является бин операцией
//					if (find(control_const.begin(), control_const.end(), actual_string) != control_const.end())
//					{
//						operands[actual_string] = value_for_const[actual_string];
//					} // проверка что actual_string является константой и установка значения
//					else operands[actual_string] = 0.0;
//					infix.push_back(static_cast<Term*>(new Var(actual_string, operands))); // правильно ли передаю operands?
//					infix.push_back(static_cast<Term*>(new Function(string(1, str[i++]))));
//					actual_string = "";
//					condition = Stat::S0;
//					break;
//				}
//				if (str[i] == '(') {  // closed
//					if (find(control_func_unary.begin(), control_func_unary.end(), actual_string) != control_func_unary.end()) {  // проверка что текущая строка является функцией
//						infix.push_back(static_cast<Term*>(new Function(actual_string, 0))); actual_string = ""; infix.push_back(static_cast<Term*>(new Brecket(str[i++]))); condition = Stat::S0; break;
//					}
//					else { condition = Stat::Error; break; }
//				}
//				if (str[i] == ')') {  // closed
//					if (find(control_const.begin(), control_const.end(), actual_string) != control_const.end()) operands[actual_string] = value_for_const[actual_string]; // проверка что actual_string является константой и установка значения
//					else operands[actual_string] = 0.0;
//					infix.push_back(static_cast<Term*>(new Var(actual_string, operands))); // правильно ли передаю operands?
//					infix.push_back(static_cast<Term*>(new Brecket(str[i++]))); actual_string = ""; condition = Stat::S0; break;
//					}
//				else { condition = Stat::Error; break; }
//			default: condition = Stat::Error; break;
//
//		}
//		if (condition == Stat::Error) return i + 1;
//	}
//	infix.pop_back();
//	return 0;
//}
//
//
//int Translator::SyntaxParce() {
//	enum class Stat { S0, Snumb1, Soperation, Error };
//	Stat condition = Stat::S0;
//	string actual_string = "";
//	int i = 0;
//	int count_bracket = 0;
//	for (int i = 0; i < infix.size(); i++) {
//		Term* term = infix[i];
//		switch (condition) {
//		case Stat::S0: 
//			if (dynamic_cast<Number*>(term)) { condition = Stat::Snumb1; break; }
//			if (dynamic_cast<Var*>(term)) { condition = Stat::Snumb1; break; }
//			if (dynamic_cast<Brecket*>(term)) {
//				Brecket* b = dynamic_cast<Brecket*>(term);
//				char b_type = b->GetBracketType();
//				if (b_type == '(') { count_bracket += 1; }
//				if (b_type == ')') { count_bracket -= 1; condition=Stat::Snumb1; }
//				break;
//			}
//			if (dynamic_cast<Function*>(term)) {
//				Function* f = dynamic_cast<Function*>(term);
//				string name_func = f->GetName();
//				if (name_func[0] == '+' || name_func[0] == '-') {
//					f->ChangeIsBin(0);
//				} // является ли изменение бинарности операции хорошим тоном?
//				int func_type = f->GetIsBin();
//				if (func_type == 0) { condition = Stat::Soperation; }
//				else { condition = Stat::Error; }
//				break;
//			}
//			else { condition = Stat::Error; break; }
//		case Stat::Snumb1: // closed?
//			if (dynamic_cast<Function*>(term)) {
//				Function* f = dynamic_cast<Function*>(term);
//				int func_type = f->GetIsBin();
//				if (func_type == 1) { condition = Stat::Soperation; }
//				else { condition = Stat::Error;}
//				break;
//			}
//			if (dynamic_cast<Brecket*>(term)) {
//				Brecket* b = dynamic_cast<Brecket*>(term);
//				char b_type = b->GetBracketType();
//				if (b_type == ')') { count_bracket -= 1; condition = Stat::Snumb1; }
//				else { condition = Stat::Error; }
//				break;
//			}
//			else { condition = Stat::Error; break; }
//		case Stat::Soperation:
//			if (dynamic_cast<Function*>(term)) {
//				Function* f = dynamic_cast<Function*>(term);
//				int func_type = f->GetIsBin();
//				if (func_type == 0) { condition = Stat::Soperation; }
//				else { condition = Stat::Error; break; }
//				break;
//			}
//			if (dynamic_cast<Number*>(term)) { condition = Stat::Snumb1; break; }
//			if (dynamic_cast<Var*>(term)) { condition = Stat::Snumb1; break; }
//			if (dynamic_cast<Brecket*>(term)) {
//				Brecket* b = dynamic_cast<Brecket*>(term);
//				char b_type = b->GetBracketType();
//				if (b_type == '(') { count_bracket += 1; condition = Stat::S0; }
//				if (b_type == ')') { count_bracket -= 1; condition = Stat::Snumb1; } // Не должно быть?
//				break;
//			}
//			else { condition = Stat::Error; break; }
//	}
//		if (count_bracket < 0) { return -1; }
//		if (condition == Stat::Error) return -1;
//	}
//	if (count_bracket > 0) { return -1; }
//	if (condition == Stat::Soperation) { return -1; }
//	return 0;
//}
//
//void Translator::ToPostfix() {
//	map<string, int> priority;
//	priority = { {string(1, '+'), 1}, {string(1, '-'), 1}, {string(1, '*'), 2}, {string(1, '^'), 3}, {string(1, '/'), 2}, {"sin", 4}, {"cos", 4}, {"tg", 4} , {"abs", 4}};  // где лучше всего в программе расположить?
//	Stack<Term*> st;
//	for (Term* term : infix) {
//		if (dynamic_cast<Number*>(term) || dynamic_cast<Var*>(term)) { postfix.push_back(term); }
//		if (dynamic_cast<Brecket*>(term)) {
//			Brecket* b = dynamic_cast<Brecket*>(term);
//			char b_type = b->GetBracketType();
//			if (b_type == '(') { st.Push(term); }
//			else {
//				Term* term_tmp = static_cast<Term*>(st.Pop());
//				while (!(dynamic_cast<Brecket*>(term_tmp))) {
//					postfix.push_back(term_tmp);
//					term_tmp = static_cast<Term*>(st.Pop());
//				}
//			}
//		}
//		if (dynamic_cast<Function*>(term)) {
//			while (!st.IsEmpty()) {
//				Term* term_tmp = static_cast<Term*>(st.Pop());
//				if (dynamic_cast<Brecket*>(term_tmp)) {
//					st.Push(term_tmp);
//					break;
//				}
//				Function* f = dynamic_cast<Function*>(term);
//				Function* f_tmp = dynamic_cast<Function*>(term_tmp);
//				string name_f = f->GetName();
//				string name_f_tmp = f_tmp->GetName();
//				if (priority[name_f] <= priority[name_f_tmp]) {
//					postfix.push_back(term_tmp);
//				}
//				else {
//					st.Push(term_tmp);
//					break;
//				}
//			}
//			st.Push(term);
//		}
//	}
//	while (!st.IsEmpty()) {
//		postfix.push_back(st.Pop());
//	}
//}
//
//double Translator::Calculate(const map<string, double>& values) {
//	if (!status) throw 1;
//	for (auto item : values) {
//		try {
//			operands.at(item.first) = item.second;
//		}
//		catch (out_of_range& e) { throw 1; }
//	}
//	ToPostfix();
//	Stack<double> st;
//	double leftOperand, rightOperand;
//	for (Term* term : postfix) {
//		if (dynamic_cast<Number*>(term)) {
//			Number* numb = dynamic_cast<Number*>(term);
//			st.Push(numb->GetValue());
//		}
//		if (dynamic_cast<Var*>(term)) {
//			Var* var = dynamic_cast<Var*>(term);
//			st.Push(var->GetValue());
//		}
//		if (dynamic_cast<Function*>(term)) {
//			Function* func = dynamic_cast<Function*>(term);
//			int stat_bin = func->GetIsBin();
//			if (stat_bin) {
//				rightOperand = st.Pop();
//				leftOperand = st.Pop();
//				st.Push(func->function(leftOperand, rightOperand));
//			}
//			if (!stat_bin) {
//				leftOperand = st.Pop();
//				st.Push(func->function(leftOperand));
//			}
//		}
//	}
//	return st.Pop();
//}
