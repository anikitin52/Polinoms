#include <gtest.h>
#include "AVLtree.h"

TEST(AVLtree, CanCreateAVLtree) {
	ASSERT_NO_THROW(AVLtree t1);
}
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