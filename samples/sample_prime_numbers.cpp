

#include <iomanip>


#ifndef USE_SET

#include <iostream>
#include <string>
#include "RedBlackTree.h"
#include <gtest.h>
#include <stdio.h>

int main()
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
	cout << "Hallo";
	cout << t.size() << endl;
	cout << t.InCorrectBalanceTree();
	//cout << t.InCorrectBalanceTree() << endl;
	//cout << t.size();
}
#endif