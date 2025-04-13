#include "RedBlackTree.h"
#include <gtest.h>
#include <string>
#include <stdio.h>

TEST(RedBlackTree, CanCreateRedBlackTree)
{
	ASSERT_NO_THROW(RedBlackTree t());
}


TEST(RedBlackTree, CanInsertRedBlackTree)
{
	RedBlackTree t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	EXPECT_EQ(t.Insert("1x^3y^4z^5", p), true);
}


TEST(RedBlackTree, NotCanInsertExistsKey)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("8", p3);
	EXPECT_EQ(t.Insert("2", p2), false);
}


TEST(RedBlackTree, CanDeleteRedBlackTree)
{
	RedBlackTree t;
	Polinom p("0x^5y^9z^8+1x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p);
	EXPECT_EQ(t.Delete("1x^3y^4z^5"), true);
}


TEST(RedBlackTree, NotCanDeleteNotKey)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Delete("7x^3y^4z^5"), false);
}

TEST(RedBlackTree, NotCanDeleteForEmty)
{
	RedBlackTree t;
	EXPECT_EQ(t.Delete("7x^3y^4z^5"), false);
}

TEST(RedBlackTree, CorrectFind1)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p2);
}

TEST(RedBlackTree, CorrectFind2)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("0x^3y^4z^5", p3);
	t.Insert("9x^3y^4z^5", p1);
	t.Insert("1x^3y^4z^5", p3);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p2);
}


TEST(RedBlackTree, FindReturnNullForNotKey)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	EXPECT_EQ(t.Find("66x^3y^4z^5"), nullptr);
}

TEST(RedBlackTree, FindReturnNullForEmptyTree)
{
	RedBlackTree t;
	EXPECT_EQ(t.Find("66x^3y^4z^5"), nullptr);
}

TEST(RedBlackTree, CanModernizirenFind)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1x^3y^4z^5", p1);
	t.Insert("2x^3y^4z^5", p2);
	t.Insert("8x^3y^4z^5", p3);
	*t.Find("2x^3y^4z^5") = p3;
	EXPECT_EQ(*t.Find("2x^3y^4z^5"), p3);
}


TEST(RedBlackTree, CorrectDelete)
{
	bool correct = true;
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("8", p2);
	t.Insert("50", p2);
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("4", p3);
	t.Delete("4");
	// proverka correctnosti
	correct = correct && (!t.Insert("1", p3));
	correct = correct && (!t.Insert("2", p3));
	correct = correct && (!t.Insert("8", p3));
	correct = correct && (!t.Insert("50", p3));
	correct = correct && (!t.Delete("4"));
	EXPECT_EQ(correct, true);
	EXPECT_EQ(t.InCorrectBalanceTree(), true);
}

TEST(RedBlackTree, InsertSituation1)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");

	t.Insert("1", p1);

	bool correct = (t.size() == 1) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}

TEST(RedBlackTree, InsertSituation2)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	t.Insert("1", p1);
	// parent чёрный
	t.Insert("2", p2);
	bool correct = (t.size() == 2) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}

TEST(RedBlackTree, InsertSituation3)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("8", p3);
	// дядя красный
	t.Insert("9", p3);
	bool correct = (t.size() == 4) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}


TEST(RedBlackTree, InsertSituation4)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("5", p1);
	t.Insert("4", p2);
	t.Insert("3", p3);
	t.Insert("2", p3);
	// дядя чёрный
	t.Insert("1", p3);
	bool correct = (t.size() == 5) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}

TEST(RedBlackTree, InsertBigSituation3)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("3", p3);
	t.Insert("4", p3);
	t.Insert("5", p3);
	t.Insert("6", p3);
	// t.print();
	bool correct = (t.size() == 6) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}


TEST(RedBlackTree, DeleteSituationForYBlackAndAnyBaby)
{
	RedBlackTree t;

	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("3", p3);
	t.Insert("4", p3);
	//t.print();
	t.Delete("4");
	//t.print();
	bool correct = (t.size() == 3) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}

TEST(RedBlackTree, DeleteSituationForYRed)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("4", p3);
	//t.print();
	t.Delete("4");
	//t.print();
	bool correct = (t.size() == 2) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}

// если удаляемый лист - чёрный и не имеет детей

TEST(RedBlackTree, DeleteSituation1)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("8", p3);
	// дядя красный
	t.Insert("9", p3);
	bool correct = (t.size() == 4) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}


TEST(RedBlackTree, DeleteSituation4)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	Polinom p2("2x ^ 3y ^ 4z ^ 5");
	Polinom p3("8x^3y^4z^5");
	t.Insert("1", p1);
	t.Insert("2", p2);
	t.Insert("3", p3);
	t.Insert("4", p3);
	// дядя чёрный
	t.Insert("5", p3);
	bool correct = (t.size() == 5) && t.InCorrectBalanceTree();
	EXPECT_EQ(correct, true);
}

TEST(RedBlackTree, DeleteBalanceAllSituation)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	for (int i = 0; i < 10; i++) {
		t.Insert(std::to_string(i), p1);
	}
	bool correct = (t.size() == 10) && t.InCorrectBalanceTree();
	//t.print();
	for (int i = 0; i < 10; i++) {
		//cout << i << " ";
		t.Delete(std::to_string(i));
		//t.print();
		correct = correct && (t.size() == 9 - i) && t.InCorrectBalanceTree(); // balance and correct size
	}
	correct = correct && t.Empty();
	EXPECT_EQ(correct, true);
}


TEST(RedBlackTree, ConstrutrorCopy)
{
	RedBlackTree t1;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	for (int i = 0; i < 10; i++) {
		t1.Insert(std::to_string(i), p1);
	}
	RedBlackTree t2(t1);
	bool correct = (t2.size() == 10) && (t2.InCorrectBalanceTree());
	EXPECT_EQ(correct, true);
}

TEST(RedBlackTree, MillionElements)
{
	RedBlackTree t;
	Polinom p1("0x^5y^9z^8+1x^3y^4z^5");
	for (int i = 0; i < 1000000; i++) {
		t.Insert(std::to_string(i), p1);
	}
	for (int i = 0; i < 10000000; i++) {
		// cout << i << endl;
		if (i == 2000) {
			t.Delete(std::to_string(i));
		}
		else t.Delete(std::to_string(i));
	}
	EXPECT_EQ(t.Empty(), true);
}