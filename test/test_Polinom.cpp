#include "Polinom.h"
#include <gtest.h>

TEST(Polinom, CanCreateCorrectPolinom) {
	ASSERT_NO_THROW(Polinom pol1("3.2x^3y^1z^2+14.36x^1y^4z^3"));
}

// Проверка корректронсти работы парсера и проверки синтаксиса и правильности ввода числел 
// Методы: Parse(), GrammarCheck(), LexicalCheck()
TEST(Polinom, PolinomStartFromPlus) {
	ASSERT_NO_THROW(Polinom pol1("+3.2x^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, PolinomStartsFromMinus) {
	ASSERT_NO_THROW(Polinom pol1("-3.2x^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, PolinomStartsFromOtherSymbol) {
	ASSERT_ANY_THROW(Polinom pol1("*3.2x^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotDoubleNumAfterSign1) {
	ASSERT_ANY_THROW(Polinom pol1("+3.2x^3y^1z^2++14.3x^1y^4z^3"));
}
TEST(Polinom, NotDoubleNumAfterSign2) {
	ASSERT_ANY_THROW(Polinom pol1("3.2.1x^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotDoubleNumAfterSign3) {
	ASSERT_ANY_THROW(Polinom pol1("+.3x^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotXAfterDoubleNum) {
	ASSERT_ANY_THROW(Polinom pol1("3.2yx^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotDegSignAfterX) {
	ASSERT_ANY_THROW(Polinom pol1("3.2xx^3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotDegSignAfterY) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3yy^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotDegSignAfterZ) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^1z^2+14.3x^1y^4zz^3"));
}
TEST(Polinom, NotIntNumberAfterDegSignX) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^x3y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotIntNumberAfterDegSignY) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^y1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotIntNumberAfterDegSignZ) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^1z^z2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotYAfterDegree) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3qy^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotZAfterDegree) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^1qz^2+14.3x^1y^4z^3"));
}
TEST(Polinom, NotSignNumberAfterDegZ) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^1z^2q+14.3x^1y^4z^3"));
}
TEST(Polinom, DegXMore9) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^33y^1z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, DegYMore9) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^11z^2+14.3x^1y^4z^3"));
}
TEST(Polinom, DegZMore9) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^1z^2+14.3x^1y^4z^33"));
}
TEST(Polinom, DegXLess0) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^-3y^1z^2+14.3x^1y^4z^33"));
}
TEST(Polinom, DegYLess0) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^-1z^2+14.3x^1y^4z^33"));
}
TEST(Polinom, DegZLess0) {
	ASSERT_ANY_THROW(Polinom pol1("3.2x^3y^1z^-2+14.3x^1y^4z^33"));
}


