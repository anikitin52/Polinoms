#include "Tablice.h"
#include <gtest.h>

TEST(Tablice, CanCreateTable)
{
	ASSERT_NO_THROW(Table t());
}


TEST(Tablice, CanInsertTable)
{
	Table t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	EXPECT_EQ(t.Insert("1x^3y^4z^5", p), true);
}

TEST(Tablice, NotCanInsertExistsKey)
{
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Insert("2x^3y^4z^5", p2), false);
}


TEST(Tablice, CanDeleteTable)
{
	Table t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p);
	EXPECT_EQ(t.Delete("1x^3y^4z^5"), true);
}

TEST(Tablice, NotCanDeleteNotKey)
{
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Delete("7x^3y^4z^5"), false);
}

TEST(Tablice, CorrectFind)
{
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p2);
}

TEST(Tablice, FindReturnNullForNotKey)
{
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Find("66x^3y^4z^5"), nullptr);
}

TEST(Tablice, CanModernizirenFind)
{
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	*t.Find("2x^3y^4z^5") = p3;
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p3);
}

TEST(Tablice, CorrectReturnSize)
{
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.size(), 3);
}

TEST(Tablice, CorrectReturnSizeForEmptyTable)
{
	Table t;
	EXPECT_EQ(t.size(), 0);
}

/*
TEST(iterator, can_create_iterator_point_to_first) {
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
    Table::iterator it1 = t.begin();
    EXPECT_EQ(it1.value(), p1);
}


TEST(iterator, can_increment_the_iterator_by_a_number) {
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	Table::iterator it1(t.begin());
	it1 + 2;
	EXPECT_EQ(it1.value(), p3);
	EXPECT_EQ(it1.key(), "8x^3y^4z^5");
}


TEST(iterator, correct_prefix_increment) {
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	Table::iterator it1(t.begin());
    EXPECT_EQ((it1++).value(), p1);
    EXPECT_EQ(it1.value(), p2);
}


TEST(iterator, correct_postfix_increment) {
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	Table::iterator it1(t.begin());
	EXPECT_EQ((++it1).value(), p2);
	EXPECT_EQ(it1.value(), p2);
}


TEST(iterator, correct_end_iterator) {
	Table t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	Table::iterator it1(t.begin());
	Table::iterator it2(t.end());
	it1 + t.size();
	EXPECT_EQ(it1, it2);
}
*/