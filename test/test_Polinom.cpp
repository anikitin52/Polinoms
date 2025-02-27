#include "Polinom.h"
#include <gtest.h>
/*
TEST(Initialization, can_create_translator_for_the_correct_string)
{
	ASSERT_NO_THROW(Translator t("a+2"));
}

TEST(Initialization, can_create_translator_for_a_non_correct_string)
{
	ASSERT_NO_THROW(Translator t("a+2))+8."));
}


TEST(Initialization, can_return_correct_get_status)
{
	Translator t("(a + b)/7 - 6 * sin(x) + PI");
	EXPECT_EQ(1, t.GetStatus());
}

TEST(Initialization, can_return_error_code_get_status_for_syntax_a_non_correct_string)
{
	Translator t("((a + b)/7 -) 6 * sin(x) + PI");
	EXPECT_EQ(0, t.GetStatus());
}

TEST(Initialization, can_return_error_code_get_status_for_lexem_a_non_correct_string)
{
	Translator t("(a + b)/7. - 6 * 5");
	EXPECT_EQ(0, t.GetStatus());
}


TEST(Initialization, can_correct_return_get_operands)
{
	Translator t("a+b*c + sin(x)");
	vector<string> ans{ "a", "b", "c", "x" };
	EXPECT_EQ(ans, t.GetOperands());
}

TEST(Calculate, can_create_calculate_for_the_correct_string)
{
	Translator t("a+2");
	map<string, double> values{
		{"a", 5}
	};
	ASSERT_NO_THROW(t.Calculate(values));
}

TEST(Calculate, not_can_create_calculate_for_a_non_correct_string)
{
	Translator t("a+2))");
	map<string, double> values{
		{"a", 5}
	};
	ASSERT_ANY_THROW(t.Calculate(values));
}

TEST(Calculate, not_can_create_calculate_for_a_non_correct_values_argument)
{
	Translator t("a+2))");
	map<string, double> values{
		{"a", 5}, {"b", 7}
	};
	ASSERT_ANY_THROW(t.Calculate(values));
}


TEST(Calculate, cant_divide_0)
{
	Translator t("a/b");
	map<string, double> values{
		{"a", 5}, {"b", 0}
	};
	ASSERT_ANY_THROW(t.Calculate(values));
}

TEST(Calculate, correct_return_for_expression_with_staples)
{
	Translator t("((a + b)/7 - 5) + sin(PI/2)");
	map<string, double> values{
		{"a", 20}, {"b", 8}
	};
	double tmp = t.Calculate(values);
	EXPECT_EQ(0, tmp);
}

TEST(Calculate, correct_return_for_correct_expression)
{
	Translator t("a*2 + 99");
	map<string, double> values{
		{"a", 1.2}
	};
	EXPECT_EQ(101.4, t.Calculate(values));
}

TEST(Calculate, correct_return_for_expression_with_unary_minus_and_unary_plus)
{
	Translator t("(-7*10+5)+(+20)");
	map<string, double> values{};
	EXPECT_EQ(-45, t.Calculate(values));
}

TEST(Calculate, correct_return_for_expression_with_space)
{
	Translator t("    12+   7 -6 *    2");
	map<string, double> values{};
	EXPECT_EQ(7, t.Calculate(values));
}
*/