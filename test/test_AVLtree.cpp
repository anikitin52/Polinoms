#include <gtest.h>
#include "AVLtree.h"

// Создание дерева
TEST(AVLtree, CanCreateAVLtree) {
	ASSERT_NO_THROW(AVLtree t1);
}
TEST(AVLtree, CanInsertElement) {
	AVLtree tree;

	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	ASSERT_NO_THROW(tree.Insert("a", p1));
}

// Вставка 
TEST(AVLtree, CantInsertNotUniqueElement) {
	AVLtree tree;

	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	Polinom p2("4x^5y^9z^8+2x^3y^4z^5");
	tree.Insert("a", p1);
	ASSERT_ANY_THROW(tree.Insert("a", p2));
}
TEST(AVLtree, InsertIntoEmptyTree) {
	AVLtree tree;

	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	tree.Insert("a", p1);

	ASSERT_NE(tree.Find("a"), nullptr);
}
TEST(AVLtree, InsertMillionElements) {
	AVLtree tree;

	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	const int million = 1000000;
	
	for (int i = 0; i < million; i++) {
		tree.Insert(to_string(i), p1);
		if (i % 100000 == 0) cout << i << "\n";
	}
}
TEST(AVLtree, CorrectInsertToLeftSubtreeCausesRightRotation) {
	AVLtree tree;
	tree.Insert("c", Polinom("1"));
	tree.Insert("b", Polinom("2"));
	tree.Insert("a", Polinom("3"));
	// После вставки "a" баланс корня нарушается, выполняется правый поворот
	ASSERT_NE(tree.Find("b"), nullptr);
}

TEST(AVLtree, InsertToRightSubtreeCausesLeftRotation) {
	AVLtree tree;
	tree.Insert("a", Polinom("1"));
	tree.Insert("b", Polinom("2"));
	tree.Insert("c", Polinom("3"));
	// После вставки "c" баланс корня нарушается, выполняется левый поворот
	ASSERT_NE(tree.Find("b"), nullptr);
}

TEST(AVLtree, InsertCausesLeftRightRotation) {
	AVLtree tree;
	tree.Insert("c", Polinom("1"));
	tree.Insert("a", Polinom("2"));
	tree.Insert("b", Polinom("3"));
	// Вставка "b" вызывает двойной поворот (левый-правый)
	ASSERT_NE(tree.Find("b"), nullptr);
	//ASSERT_EQ(tree.Find("c")->ToString(), "1");
}
TEST(AVLtree, InsertCausesRightLeftRotation) {
	AVLtree tree;
	tree.Insert("a", Polinom("1"));
	tree.Insert("c", Polinom("2"));
	tree.Insert("b", Polinom("3"));
	// Вставка "b" вызывает двойной поворот (правый-левый)
	ASSERT_NE(tree.Find("b"), nullptr);
	//ASSERT_EQ(tree.Find("a")->ToString(), "1");
}

// Удаление 
TEST(AVLtree, DeleteLeafWithoutRebalance) {
	AVLtree tree;
	tree.Insert("b", Polinom("1"));
	tree.Insert("a", Polinom("2"));
	tree.Delete("a");
	// Удаление листа "a" не нарушает баланс
	ASSERT_EQ(tree.Find("a"), nullptr);
	ASSERT_NE(tree.Find("b"), nullptr);
}
TEST(AVLtree, DeleteNodeWithTwoChildrenRequiresBalance) {
	AVLtree tree;
	tree.Insert("d", Polinom("1"));
	tree.Insert("b", Polinom("2"));
	tree.Insert("f", Polinom("3"));
	tree.Insert("a", Polinom("4"));
	tree.Insert("c", Polinom("5"));
	tree.Delete("b");
	// Удаление "b" заменяется на "a" или "c", требуется балансировка
	ASSERT_EQ(tree.Find("b"), nullptr);
	ASSERT_NE(tree.Find("c"), nullptr);
}
TEST(AVLtree, DeleteCausesRightRotationAfter) {
	AVLtree tree;
	tree.Insert("c", Polinom("1"));
	tree.Insert("b", Polinom("2"));
	tree.Insert("d", Polinom("3"));
	tree.Insert("a", Polinom("4"));
	tree.Delete("d");
	// Удаление "d" нарушает баланс, требуется правый поворот
	ASSERT_EQ(tree.Find("d"), nullptr);
	ASSERT_NE(tree.Find("b"), nullptr);
}
TEST(AVLtree, DeleteCausesLeftRightRotationUpwards) {
	AVLtree tree;
	tree.Insert("e", Polinom("1"));
	tree.Insert("b", Polinom("2"));
	tree.Insert("f", Polinom("3"));
	tree.Insert("a", Polinom("4"));
	tree.Insert("d", Polinom("5"));
	tree.Insert("c", Polinom("6"));
	tree.Delete("f");
	// Удаление "f" вызывает двойной поворот вверх по дереву
	ASSERT_EQ(tree.Find("f"), nullptr);
	ASSERT_NE(tree.Find("d"), nullptr);
}
TEST(AVLtree, InsertDeleteManyElements) {
	const int many = 100000;
	AVLtree tree;
	Polinom p1("4x^5y^9z^8+2x^3y^4z^5");
	

	for (int i = 0; i < many; i++) {
		tree.Insert(to_string(i), p1);
		if (i % 1000 == 0) cout << i << "\n";
	}
	for (int i = 0; i < many; i++) {
		tree.Delete(to_string(i));
		if (i % 1000 == 0) cout << many - i << "\n";
	}
}