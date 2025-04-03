#include <gtest.h>
#include <string>
#include "Polinom.h"
#include "SortedTable.h"

TEST(SortedTable, CanCreateSortedTable) {
	ASSERT_NO_THROW(SortedTable t1);
}
// Метод Insert (вставка)
TEST(SortedTable, CanInsertToTable) {
	SortedTable t1;
	string name = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	ASSERT_NO_THROW(t1.Insert(name, pol1));
}
TEST(SortedTable, InsertIfKeyExists) {
	SortedTable t1;

	string name = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");
	t1.Insert(name, pol1);

	Polinom pol2("4x^5y^9z^8+2x^3y^4z^5");
	ASSERT_ANY_THROW(t1.Insert(name, pol2));
}
TEST(SortedTable, InsertWithUniqueKey) {
	SortedTable t1;
	string name1 = "Polinom1";
	string name2 = "Polinom2";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom pol2("3x^4y^3z^2+1x^2y^1z^0");

	t1.Insert(name1, pol1);
	ASSERT_NO_THROW(t1.Insert(name2, pol2)); 
}
TEST(SortedTable, InsertAtBeginOfTable) {
	SortedTable t1;
	string name1 = "Polinom2";
	string name2 = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom pol2("3x^4y^3z^2+1x^2y^1z^0");

	t1.Insert(name1, pol1);
	ASSERT_NO_THROW(t1.Insert(name2, pol2));
}
TEST(SortedTable, InsertBeginCheckValue) {
	SortedTable t1;
	string name1 = "Polinom2";
	string name2 = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom pol2("3x^4y^3z^2+1x^2y^1z^0");

	t1.Insert(name1, pol1); 
	t1.Insert(name2, pol2); 
	Polinom* result = t1.Find(name2); 
	ASSERT_EQ(*result, pol2);
}
TEST(SortedTable, InsertInMiddle) {
	SortedTable t1;
	string name1 = "Polinom1";
	string name2 = "Polinom3";
	string name3 = "Polinom2"; 
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom pol2("3x^4y^3z^2+1x^2y^1z^0");
	Polinom pol3("2x^3y^2z^1+5x^1y^0z^2");

	t1.Insert(name1, pol1); 
	t1.Insert(name2, pol2);
	ASSERT_NO_THROW(t1.Insert(name3, pol3)); 
}

TEST(SortedTable, InsertInMiddleCheckValue) {
	SortedTable t1;
	string name1 = "Polinom1";
	string name2 = "Polinom3";
	string name3 = "Polinom2";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom pol2("3x^4y^3z^2+1x^2y^1z^0");
	Polinom pol3("2x^3y^2z^1+5x^1y^0z^2");

	t1.Insert(name1, pol1);
	t1.Insert(name2, pol2);
	t1.Insert(name3, pol3);
	Polinom* result = t1.Find(name2);
	ASSERT_EQ(*result, pol2);
}
TEST(SortedTable, InsertWithEmptyKey) {
	SortedTable t1;
	string name = "";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	ASSERT_NO_THROW(t1.Insert(name, pol1)); 
}
TEST(SortedTable, InsertWithSameValueDifferentKeys) {
	SortedTable t1;
	string name1 = "Polinom1";
	string name2 = "Polinom2";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	t1.Insert(name1, pol1); 
	ASSERT_NO_THROW(t1.Insert(name2, pol1));
}
/*
TEST(SortedTable, InsertMillionElements) {
	SortedTable t1;
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	for (int i = 0; i < 1000000; i++) {
        string name = "Polinom " + std::to_string(i);
        t1.Insert(name, pol1);
        if (i % 10000 == 0) cout << name << endl;
    }
}
*/

// Метод Delete (удаление)
TEST(SortedTable, DeleteExistingElement) {
	SortedTable t1;
	string name = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	t1.Insert(name, pol1); 
	ASSERT_NO_THROW(t1.Delete(name));
	ASSERT_EQ(t1.Find(name), nullptr); 
}
TEST(SortedTable, DeleteFromEmptyTable) {
	SortedTable t1;
	string name = "Polinom1";

	ASSERT_ANY_THROW(t1.Delete(name));
}
TEST(SortedTable, DeleteNonExistentElement) {
	SortedTable t1;
	string name = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	t1.Insert(name, pol1);
	ASSERT_ANY_THROW(t1.Delete("Polonom"));
}

// Метод Find (поиск)
TEST(SortedTable, FindExistingElement) {
	SortedTable t1;
	string name = "Polinom1";
	Polinom pol1("4x^5y^9z^8+2x^3y^4z^5");

	t1.Insert(name, pol1); 
	ASSERT_NE(t1.Find(name), nullptr); 
	ASSERT_EQ(*t1.Find(name), pol1); 
}
TEST(SortedTable, FindNonExistentElement) {
	SortedTable t1;
	string name = "Polinom1";

	ASSERT_EQ(t1.Find(name), nullptr); 
}
TEST(SortedTable, FindInEmptyTable) {
	SortedTable t1;
	string name = "Polinom1";

	ASSERT_EQ(t1.Find(name), nullptr); 
}