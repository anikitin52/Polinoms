#include <vector>
#include <ctype.h>
#include "Polinom.h"

void Polinom::Parse(string pol)
{
    string number; // Храним текущее число

    for (char c : pol) {
        if (isdigit(c) || c == '.') {
            number.push_back(c);
        }
        else {
            if (number != "") {
                polinom.push_back(number);
                number = "";
            }
            polinom.push_back(std::string(1, c));
        }
    }
    if (number != "") {
        polinom.push_back(number);
    }
}

bool Polinom::LexicalCheck(string number)
{
    enum class State {
        START,
        FIRST_NUMBER,
        SECOND_NUMBER,
        OTHER
    };
    vector<char> nums = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    State status = State::START;
    for (int i = 0; i < number.size(); i++) {
        switch (status) {
        case State::START:
            if (std::find(nums.begin(), nums.end(), number[i]) != nums.end()) {
                status = State::FIRST_NUMBER;
            }
            else {
                status = State::OTHER;
            }
            break;
        case State::FIRST_NUMBER:
            if (std::find(nums.begin(), nums.end(), number[i]) != nums.end()) {
                status = State::FIRST_NUMBER;
            }
            else if (number[i] == '.') {
                status = State::SECOND_NUMBER;
            }
            else {
                status = State::OTHER;
            }
            break;
        case State::SECOND_NUMBER:
            if (std::find(nums.begin(), nums.end(), number[i]) != nums.end()) {
                status = State::SECOND_NUMBER;
            }
            else {
                status = State::OTHER;
            }
            break;
        default:
            break;
        }


        if (status == State::OTHER) {
            return false;
        }


    }
    return status != State::OTHER;
}

bool Polinom::SyntaxCheck()
{
    pair<int, double> elem;
    double ratio;
    string degree;
    enum class State {
        // Показывает то, что мы получили 
        START,
        SIGN,
        DOUBLE_NUM,
        X,
        DEG_SIGN_X,
        DEG_X,
        Y,
        DEG_SIGN_Y,
        DEG_Y,
        Z,
        DEG_SIGN_Z,
        DEG_Z,
        ERROR,
        SUCCESS
    };

    bool isMinus = false;
    State status = State::START;
    for (string lexem : polinom) {
        switch (status) {
        case State::START:
            if (lexem == "+" || lexem == "-") {
                if (lexem == "-") {
                    isMinus = true;
                }
                status = State::SIGN;
            }
            else if (lexem[0] >= '0' && lexem[0] <= '9') {
                if (!LexicalCheck(lexem)) {
                    return false;
                }
                ratio = stod(lexem);
                if (isMinus) {
                    ratio = -ratio;
                }
                status = State::DOUBLE_NUM;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::SIGN:
            if (lexem[0] >= '0' && lexem[0] <= '9') {
                if (!LexicalCheck(lexem)) {
                    return false;
                }
                ratio = stod(lexem);
                if (isMinus) {
                    ratio = -ratio;
                    isMinus = false;
                }
                status = State::DOUBLE_NUM;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DOUBLE_NUM:
            if (lexem == "x") {
                status = State::X;
            }
            else if (lexem == "+" || lexem == "-") {
                if (lexem == "-") {
                    isMinus = true;
                }
                status = State::SIGN;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::X:
            if (lexem == "^") {
                status = State::DEG_SIGN_X;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DEG_SIGN_X:
            if (lexem[0] >= '0' && lexem[0] <= '9' && lexem.size() == 1) {
                degree.push_back(lexem[0]);
                status = State::DEG_X;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DEG_X:
            if (lexem == "y") {
                status = State::Y;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::Y:
            if (lexem == "^") {
                status = State::DEG_SIGN_Y;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DEG_SIGN_Y:
            if (lexem[0] >= '0' && lexem[0] <= '9' && lexem.size() == 1) {
                degree.push_back(lexem[0]);
                status = State::DEG_Y;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DEG_Y:
            if (lexem == "z") {
                status = State::Z;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::Z:
            if (lexem == "^") {
                status = State::DEG_SIGN_Z;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DEG_SIGN_Z:
            if (lexem[0] >= '0' && lexem[0] <= '9' && lexem.size() == 1) {
                degree.push_back(lexem[0]);
                elem = make_pair(stoi(degree), ratio);
                data.push_back(elem);
                degree = "";
                status = State::DEG_Z;
            }
            else {
                status = State::ERROR;
            }
            break;
        case State::DEG_Z:
            if (lexem == "+" || lexem == "-") {
                if (lexem == "-") {
                    isMinus = true;
                }
                status = State::SIGN;
            }
            else {
                status = State::ERROR;
            }
            break;
        default:
            status = State::ERROR;
        }
        if (status == State::ERROR) {
            return false;
        }
    }
    if (status == State::DEG_Z || status == State::DEG_Y || status == State::DEG_X || status == State::DOUBLE_NUM) {
        status = State::SUCCESS;
    }
    return status == State::SUCCESS;
}


Polinom::Polinom()
{
    size = 0;
}

Polinom::Polinom(string pol)
{
    Parse(pol);
    if (!SyntaxCheck()) {
        throw "ERROR! Invalid Syntax!";
    }
    /*
    for (auto el : data) {
        cout << el.second << " " << el.first << "\n";
    }
    */
}

void Polinom::print()
{
    for (auto el : data) {
        cout << el.second << "x^" << to_string(el.first)[0] << "y^" << to_string(el.first)[1] << "z^" << to_string(el.first)[2] << "\n";
    }
}

Polinom& Polinom::operator+(Polinom pol)
{
    for (auto el : pol.data) {
        bool found = false;
        for (auto& it : data) {
            if (it.first == el.first) {
                it.second += el.second;
                found = true;
                break;
            }
        }
        if (!found) {
            data.push_back(el);
        }
    }
    return *this;
}

Polinom& Polinom::operator-(Polinom pol)
{
    for (auto el : pol.data) {
        bool found = false;
        for (auto& it : data) {
            if (it.first == el.first) {
                it.second -= el.second;
                found = true;
                break;
            }
        }
        if (!found) {
            data.push_back(make_pair(el.first, -el.second));
        }
    }
    return *this;
}

Polinom& Polinom::operator*(double c)
{
    for (auto& el : data) {
        el.second *= c;
    }
    return *this;
}

Polinom& Polinom::operator*(Polinom pol)
{
    List<pair<int, double>> newData;
    for (auto el1 : data) {
        for (auto el2 : pol.data) {
            newData.push_back(make_pair(el1.first + el2.first, el1.second * el2.second));
        }
    }
    data = newData;
    return *this;
}

Polinom& Polinom::operator/(double c)
{
    for (auto& el : data) {
        el.second /= c;
    }
    return *this;
}


