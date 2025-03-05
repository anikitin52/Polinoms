#include "Polinom.h"
#include <gtest.h>

TEST(Polinom, CanCreateCorrectPolinom) {
	ASSERT_NO_THROW(Polinom pol1("3.2x^3y^1z^2+14.36x^1y^4z^3"));
}

// �������� ������������� ������ ������� � �������� ���������� � ������������ ����� ������ 
// ������: Parse(), GrammarCheck(), LexicalCheck()
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

// ������������ ������� + - * /
TEST(Polinom, TestPlus) {
	Polinom pol1("3.2x^3y^1z^2+14.36x^1y^4z^3");
	Polinom pol2("1.2x^3y^1z^2+4.36x^1y^4z^3");
	pol1 = pol1 + pol2;
	ASSERT_EQ(pol1.get_data()[0].second, 4.4);
	ASSERT_EQ(pol1.get_data()[1].second, 18.72);
}
TEST(Polinom, TestMinus) {
	Polinom pol1("3.2x^3y^1z^2+14.36x^1y^4z^3");
	Polinom pol2("1.2x^3y^1z^2+4.36x^1y^4z^3");
	pol1 = pol1 - pol2;
	ASSERT_EQ(pol1.get_data()[0].second, 2);
	ASSERT_EQ(pol1.get_data()[1].second, 10);
}
TEST(Polinom, TestMultConst) {
	Polinom pol1("3.2x^3y^1z^2+14.36x^1y^4z^3");
	pol1 = pol1 * 2.5;
	ASSERT_EQ(pol1.get_data()[0].second, 8);
	ASSERT_EQ(pol1.get_data()[1].second, 35.9);
}
TEST(Polinom, MultPolinomSize) {
	Polinom pol1("3x^3y^1z^2+2x^1y^4z^3");
	Polinom pol2("1x^3y^1z^2+4x^1y^4z^3");
	
	Polinom result = pol1 * pol2;
	ASSERT_EQ(result.get_data().size(), 3);
}
TEST(Polinom, TestMultPolinom) {
	Polinom pol1("3x^3y^1z^2+2x^1y^4z^3");
	Polinom pol2("1x^3y^1z^2+4x^1y^4z^3");

	Polinom result = pol1 * pol2;

	ASSERT_EQ(result.get_data()[0].second, 3);        
	ASSERT_EQ(result.get_data()[1].second, 14);      
	ASSERT_EQ(result.get_data()[2].second, 8);      
}
TEST(Polinom, MultPolinomDeg) {
	Polinom pol1("3x^3y^1z^2+2x^1y^4z^3");
	Polinom pol2("1x^3y^1z^2+4x^1y^4z^3");

	Polinom result = pol1 * pol2;

	ASSERT_EQ(result.get_data()[0].first, 624);
	ASSERT_EQ(result.get_data()[1]. first, 455);
	ASSERT_EQ(result.get_data()[2].first, 286);
}
TEST(Polinom, TestDivConst) {
	Polinom pol1("3.2x^3y^1z^2+14.36x^1y^4z^3");
	pol1 = pol1 / 2.5;
	ASSERT_EQ(pol1.get_data()[0].second, 1.28);
	ASSERT_EQ(pol1.get_data()[1].second, 5.744);
}

