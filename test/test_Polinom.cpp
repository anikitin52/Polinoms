#include "Polinom.h"
#include <gtest.h>

TEST(Initialization, CanCreatePolinomForTheCorrectString)
{
	ASSERT_NO_THROW(Polinom p("4x^5y^9z^8+2x^3y^4z^5"));
}

TEST(Initialization, CanCreatePolinomForTheCorrectStringForNulPolinom)
{
	ASSERT_NO_THROW(Polinom p("0x^5y^9z^8+0x^3y^4z^5"));
}


TEST(Initialization, CanCreatePolinomForANonCorrectString)
{
	ASSERT_NO_THROW(Polinom p("a+2))+8."));
}


TEST(Initialization, can_return_correct_get_status)
{
	Polinom p("4x^5y^9z^8+2x^3y^4z^5");
	EXPECT_EQ(1, p.GetStatus());
}

TEST(Initialization, can_return_error_code_get_status_for_syntax_a_non_correct_string)
{
	Polinom p("((a + b)/7 -) 6 * sin(x) + pi");
	EXPECT_EQ(0, p.GetStatus());
}


TEST(Output, CanCorrectCoutPolinomForTheCorrectString)
{
	Polinom p("4x^5y^9z^8+2x^3y^4z^5");
	ASSERT_NO_THROW(cout << p);
}

TEST(Output, NotCanCoutPolinomForNotCorrectString)
{
	Polinom p("4x^5y^9z^8+2x^3y^4z^5+*");
	ASSERT_ANY_THROW(cout << p);
}

TEST(Calculate, CanCalculateForCorrectPolinom)
{
	Polinom p("4x^5y^9z^8+2x^3y^4z^5");
	vector<double> values = { 3.5, 5.7, 6.9 };
	ASSERT_NO_THROW(p.Calculate(values));
}


TEST(Calculate, NotCanCalculateForNotCorrectPolinom)
{
	Polinom p("4x^5y^9z^8+2x^3y^4z^5+*");
	vector<double> values = { 3.5, 5.7, 6.9 };
	ASSERT_ANY_THROW(p.Calculate(values));
}


TEST(Calculate, CorrectResultCalculateForCorrectPolinomAndIntegerVector)
{
	Polinom p("4x^2y^2z^4");
	vector<double> values = { 3, 5, 2 };
	EXPECT_EQ(p.Calculate(values), 14400.0);
}


TEST(Calculate, CorrectResultCalculateForCorrectPolinomAndRealVector)
{
	Polinom p("4x^5y^9z^8");
	vector<double> values = { 3.5, 5.7, 6.9 };
	EXPECT_EQ(p.Calculate(values), 68559341881099753.89456403);
}

TEST(ComparisonOperator, IdenticalPolynomialsAreEqual)
{
	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom p2("4x^5y^9z^8+2x^3y^4z^5");
	EXPECT_EQ(p1, p2);
}

TEST(ComparisonOperator, NotIdenticalPolynomialsAreNotEqual)
{
	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom p2("7x^5y^9z^8+2x^3y^4z^5");
	EXPECT_NE(p1, p2);
}

TEST(Initialization, CanCreatePolinomForTheVectorPair)
{
	vector<pair<unsigned int, double>> vect = { {0, 15.6}, {654, 45.0} };
	ASSERT_NO_THROW(Polinom p(vect));
}

TEST(Initialization, PolynomialCreatedFromStringIsEqualToSimilarPolynomialFromVector)
{
	vector<pair<unsigned int, double>> vect = { {598, 4.6}, {345, -25} };
	Polinom p1("4.6x^5y^9z^8-25x^3y^4z^5");
	Polinom p2(vect);
	EXPECT_EQ(p1, p2);
}

TEST(ArihmeticOperation, CorrectAddition)
{
	Polinom p1("0x^1y^2z^3+4.6x^5y^9z^8+25x^3y^4z^5");
	Polinom p2("5.4x^5y^9z^8-100x^3y^4z^5+14.78x^5y^9z^9");
	Polinom p3("10x^5y^9z^8-75x^3y^4z^5+14.78x^5y^9z^9");
	Polinom p12 = p1 + p2;
	EXPECT_EQ(p12, p3);
}

TEST(ArihmeticOperation, NotCanAdditionForNotCorrectP1orP2)
{
	Polinom p1("0x^1y^2z^3+4.6x^5y^9z^8+25x^3y^4z^5");
	Polinom p2("5.4x^5y^9z^8-*/**");
	ASSERT_ANY_THROW(p1 + p2);
}

TEST(ArihmeticOperation, CorrectSub)
{
	Polinom p1("0x^1y^2z^3+4.6x^5y^9z^8+25x^3y^4z^5");
	Polinom p2("-5.4x^5y^9z^8+100x^3y^4z^5-14.78x^5y^9z^9");
	Polinom p3("+10x^5y^9z^8-75x^3y^4z^5+14.78x^5y^9z^9");
	Polinom p12 = p1 - p2;
	EXPECT_EQ(p12, p3);
}

TEST(ArihmeticOperation, NotCanSubForNotCorrectP1orP2)
{
	Polinom p1("0x^1y^2z^3+4.6x^5y^9z^8+25x^3y^4z^5");
	Polinom p2("5.4x^5y^9z^8-*/**");
	ASSERT_ANY_THROW(p1 - p2);
}

TEST(ArihmeticOperation, CorrectMulConst)
{
	Polinom p1("0x^1y^2z^3+4.6x^5y^9z^8+25x^3y^4z^5");
	Polinom p2("-32.2x^5y^9z^8-175x^3y^4z^5");
	Polinom p_mul = p1 * (-7);
	EXPECT_EQ(p2, p_mul);
}

TEST(ArihmeticOperation, NotCanMulConstForNotCorrectP1orP2)
{
	Polinom p1("5.4x^5y^9z^8-*/**");
	ASSERT_ANY_THROW(p1 * 8);
}

TEST(ArihmeticOperation, CorrectMulForNullConst)
{
	Polinom p1("0x^1y^2z^3+4.6x^5y^9z^8+25x^3y^4z^5");
	vector<pair<unsigned int, double>> vect;
	Polinom p2(vect); // empty polinom
	Polinom p_rez = p1 * 0;
	EXPECT_EQ(p2, p_rez);
}
//
//TEST(Initialization, can_return_error_code_get_status_for_lexem_a_non_correct_string)
//{
//	Translator t("(a + b)/7. - 6 * 5");
//	EXPECT_EQ(0, t.GetStatus());
//}
//
//
//TEST(Initialization, can_correct_return_get_operands)
//{
//	Translator t("a+b*c + sin(x)");
//	vector<string> ans{ "a", "b", "c", "x" };
//	EXPECT_EQ(ans, t.GetOperands());
//}
//
//TEST(Calculate, can_create_calculate_for_the_correct_string)
//{
//	Translator t("a+2");
//	map<string, double> values{
//		{"a", 5}
//	};
//	ASSERT_NO_THROW(t.Calculate(values));
//}
//
//TEST(Calculate, not_can_create_calculate_for_a_non_correct_string)
//{
//	Translator t("a+2))");
//	map<string, double> values{
//		{"a", 5}
//	};
//	ASSERT_ANY_THROW(t.Calculate(values));
//}
//
//TEST(Calculate, not_can_create_calculate_for_a_non_correct_values_argument)
//{
//	Translator t("a+2))");
//	map<string, double> values{
//		{"a", 5}, {"b", 7}
//	};
//	ASSERT_ANY_THROW(t.Calculate(values));
//}
//
//
//TEST(Calculate, cant_divide_0)
//{
//	Translator t("a/b");
//	map<string, double> values{
//		{"a", 5}, {"b", 0}
//	};
//	ASSERT_ANY_THROW(t.Calculate(values));
//}
//
//TEST(Calculate, correct_return_for_expression_with_staples)
//{
//	Translator t("((a + b)/7 - 5) + sin(PI/2)");
//	map<string, double> values{
//		{"a", 20}, {"b", 8}
//	};
//	double tmp = t.Calculate(values);
//	EXPECT_EQ(0, tmp);
//}
//
//TEST(Calculate, correct_return_for_correct_expression)
//{
//	Translator t("a*2 + 99");
//	map<string, double> values{
//		{"a", 1.2}
//	};
//	EXPECT_EQ(101.4, t.Calculate(values));
//}
//
//TEST(Calculate, correct_return_for_expression_with_unary_minus_and_unary_plus)
//{
//	Translator t("(-7*10+5)+(+20)");
//	map<string, double> values{};
//	EXPECT_EQ(-45, t.Calculate(values));
//}
//
//TEST(Calculate, correct_return_for_expression_with_space)
//{
//	Translator t("    12+   7 -6 *    2");
//	map<string, double> values{};
//	EXPECT_EQ(7, t.Calculate(values));
//}
