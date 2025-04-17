
#include <gtest.h>
#include <string>
#include <stdio.h>
#include "DirectHashTable.h"


TEST(HashTable, CanCreateTable)
{
	ASSERT_NO_THROW(HashTable<10> t());
}

TEST(HashTable, CanInsertTable)
{
	HashTable<10> t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	EXPECT_EQ(t.Insert("1x^3y^4z^5", p), true);
}

TEST(HashTable, NotCanInsertExistsKey)
{
	HashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Insert("2x^3y^4z^5", p2), false);
}


TEST(HashTable, CanDeleteTable)
{
	HashTable<10> t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p);
	EXPECT_EQ(t.Delete("1x^3y^4z^5"), true);
}

TEST(HashTable, NotCanDeleteNotKey)
{
	HashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Delete("7x^3y^4z^5"), false);
}

TEST(HashTable, CorrectFind)
{
	HashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p2);
}

TEST(HashTable, CorrectFindForNotKey)
{
	HashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Find("5"), nullptr);
}
TEST(HashTable, CanModernizirenFind)
{
	HashTable<10> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	*t.Find("2x^3y^4z^5") = p3;
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p3);
}


TEST(HashTable, RepackingForInsertElementsTheAmountIsMoreThanTheLimit)
{
	HashTable<10> t;
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


TEST(HashTable, FindPostDelete)
{
	HashTable<100> t;
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


TEST(HashTable, ConstrutrorCopy)
{
	HashTable<100> t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("41x^3y^4z^5");
	// ключи так подобраны, что проецируютс€ на одну €чейку таблицы
	t.Insert(std::to_string(0), p1);
	t.Insert(std::to_string(7), p1);
	t.Insert(">", p1);
	t.Insert("E", p2);
	t.Delete(std::to_string(7));
	t.Delete(">");
	HashTable<100> t2(t);
	bool correct = (t2.GetActualSize() == 2) && (*t2.Find("E") == p2) && (*t.Find("0") == p1);
	EXPECT_EQ(correct, true);
}

TEST(HashTable, ConstrutrorCopyForEmptyTable)
{
	HashTable<100> t;
	HashTable<100> t2(t);
	bool correct = (t2.GetActualSize() == 0);
	EXPECT_EQ(correct, true);
}


TEST(HashTable, AssignmentOperator)
{
	HashTable<5> t2;
	HashTable<5> t;
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

TEST(HashTable, AssignmentOperatorForThis)
{
	HashTable<5> t;
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

TEST(HashTable, AssignmentOperatorForEmptyTable)
{
	HashTable<100> t;
	HashTable<100> t2 = t;
	bool correct = (t2.GetActualSize() == 0);
	EXPECT_EQ(correct, true);
}


TEST(HashTable, FillingAndEmptying)
{
	HashTable<10> t;
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
