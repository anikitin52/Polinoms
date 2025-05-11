
#include <gtest.h>
#include <string>
#include <stdio.h>
#include "DirectHashTable.h"


TEST(DirectHashTable, CanCreateTable)
{
	ASSERT_NO_THROW(DirectHashTable<10> t());
}

TEST(DirectHashTable, CanInsertTable)
{
	DirectHashTable<10> t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	EXPECT_EQ(t.Insert("1x^3y^4z^5", p), true);
}

TEST(DirectHashTable, NotCanInsertExistsKey)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Insert("2x^3y^4z^5", p2), false);
}


TEST(DirectHashTable, CanDeleteTable)
{
	DirectHashTable<10> t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p);
	EXPECT_EQ(t.Delete("1x^3y^4z^5"), true);
}

TEST(DirectHashTable, NotCanDeleteNotKey)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Delete("7x^3y^4z^5"), false);
}

TEST(DirectHashTable, CorrectFind)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p2);
}

TEST(DirectHashTable, CorrectFindForNotKey)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Find("5"), nullptr);
}
TEST(DirectHashTable, CanModernizirenFind)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	*t.Find("2x^3y^4z^5") = p3;
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p3);
}


TEST(DirectHashTable, RepackingForInsertElementsTheAmountIsMoreThanTheLimit)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	bool correct = (t.GetSize() == 10);

	for (int i = 0; i < 20; i++) {
		t.Insert(std::to_string(i), p1);
		float koef = t.GetActualSize() / (float)t.GetSize();
		if (koef >= 0.8) {
			correct = false;
		}
	}
	correct = correct && (t.GetSize() == 30) && (t.GetActualSize() == 20);
	EXPECT_EQ(correct, true);
}


TEST(DirectHashTable, FindPostDelete)
{
	DirectHashTable<100> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("41x^3y^4z^5");
	// ключи так подобраны, что проецируютс€ на одну €чейку таблицы
	t.Insert(std::to_string(0), p1);
	t.Insert(std::to_string(7), p1);
	t.Insert(">", p1);
	t.Insert("E", p2);
	t.Delete(std::to_string(7));
	t.Delete(">");

	bool correct = (t.GetActualSize() == 2) && (*t.Find("E") == p2) && (*t.Find("0") == p1) && (t.Find("7") == nullptr) && (t.Find(">") == nullptr);
	EXPECT_EQ(correct, true);
}


TEST(DirectHashTable, ConstrutrorCopy)
{
	DirectHashTable<100> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("41x^3y^4z^5");
	// ключи так подобраны, что проецируютс€ на одну €чейку таблицы
	t.Insert(std::to_string(0), p1);
	t.Insert(std::to_string(7), p1);
	t.Insert(">", p1);
	t.Insert("E", p2);
	t.Delete(std::to_string(7));
	t.Delete(">");
	DirectHashTable<100> t2(t);
	bool correct = (t2.GetActualSize() == 2) && (*t2.Find("E") == p2) && (*t.Find("0") == p1);
	EXPECT_EQ(correct, true);
}

TEST(DirectHashTable, ConstrutrorCopyForEmptyTable)
{
	DirectHashTable<100> t;
	DirectHashTable<100> t2(t);
	bool correct = (t2.GetActualSize() == 0);
	EXPECT_EQ(correct, true);
}


TEST(DirectHashTable, AssignmentOperator)
{
	DirectHashTable<5> t2;
	DirectHashTable<5> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("41x^3y^4z^5");

	t2.Insert(std::to_string(55), p1);
	t2.Insert(std::to_string(23), p1);
	// ключи так подобраны, что проецируютс€ на одну €чейку таблицы
	t.Insert(std::to_string(0), p1);
	t.Insert(std::to_string(7), p1);
	t.Insert(">", p1);
	t.Insert("E", p2);
	t.Delete(std::to_string(7));
	t.Delete(">");
	t2 = t;
	bool correct = (t2.GetActualSize() == 2) && (*t2.Find("E") == p2) && (*t.Find("0") == p1);
	EXPECT_EQ(correct, true);
}

TEST(DirectHashTable, AssignmentOperatorForThis)
{
	DirectHashTable<5> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("41x^3y^4z^5");
	// ключи так подобраны, что проецируютс€ на одну €чейку таблицы
	t.Insert(std::to_string(0), p1);
	t.Insert(std::to_string(7), p1);
	t.Insert(">", p1);
	t.Insert("E", p2);
	t.Delete(std::to_string(7));
	t.Delete(">");
	t = t;
	bool correct = (t.GetActualSize() == 2) && (*t.Find("E") == p2) && (*t.Find("0") == p1);
	EXPECT_EQ(correct, true);
}

TEST(DirectHashTable, AssignmentOperatorForEmptyTable)
{
	DirectHashTable<100> t;
	DirectHashTable<100> t2 = t;
	bool correct = (t2.GetActualSize() == 0);
	EXPECT_EQ(correct, true);
}


TEST(DirectHashTable, FillingAndEmptying)
{
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("41x^3y^4z^5");
	// ключи так подобраны, что проецируютс€ на одну €чейку таблицы
	for (int i = 0; i < 10; i++) {
		t.Insert(std::to_string(i), p1);
	}
	bool correct = (t.GetActualSize() == 10);
	for (int i = 0; i < 10; i++) {
		t.Delete(std::to_string(i));
	}
	correct = correct && (t.GetActualSize() == 0);
	EXPECT_EQ(correct, true);
}


TEST(DirectHashTableiterator, can_create_iterator_point_to_first) {
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("6", p2);
	t.Insert("7", p3);
	DirectHashTable<10>::iterator it1 = t.begin();
	EXPECT_EQ(*it1, p1);
}



TEST(DirectHashTableiterator, can_increment_the_iterator_by_a_number) {
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("6", p2);
	t.Insert("7", p3);
	DirectHashTable<10>::iterator it1 = t.begin();
	it1 + 2;
	EXPECT_EQ(*it1, p3);
}

TEST(DirectHashTableiterator, correct_prefix_increment) {
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("6", p2);
	t.Insert("7", p3);
	DirectHashTable<10>::iterator it1 = t.begin();
	EXPECT_EQ(*(it1++), p1);
	EXPECT_EQ(*it1, p2);
}

TEST(DirectHashTableiterator, correct_postfix_increment) {
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("6", p2);
	t.Insert("7", p3);
	DirectHashTable<10>::iterator it1 = t.begin();
	EXPECT_EQ(*(++it1), p2);
	EXPECT_EQ(*it1, p2);
}


TEST(DirectHashTableiterator, correct_end_iterator) {
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("6", p2);
	t.Insert("7", p3);
	DirectHashTable<10>::iterator it1 = t.begin();
	DirectHashTable<10>::iterator it2 = t.end();
	it1 + t.GetActualSize();
	EXPECT_EQ(it1, it2);
}


TEST(DirectHashTableiterator, not_can_add_more_actual_size) {
	DirectHashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("6", p2);
	t.Insert("7", p3);
	DirectHashTable<10>::iterator it1 = t.begin();
	DirectHashTable<10>::iterator it2 = t.end();
	it1 + t.GetActualSize();
	ASSERT_ANY_THROW(it1 + 1);
}

TEST(DirectHashTableiterator, equality_end_begin_for_empty_table) {
	DirectHashTable<10> t;
	DirectHashTable<10>::iterator it1 = t.begin();
	DirectHashTable<10>::iterator it2 = t.end();
	EXPECT_EQ(it1, it2);
}
