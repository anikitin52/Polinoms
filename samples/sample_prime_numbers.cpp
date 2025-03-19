#include <iostream>
#include "Polinom.h"
#include <string>

int main()
{
	Polinom pol1("3x^3y^1z^2+2x^1y^4z^3");
	Polinom pol2("1x^3y^1z^2+4x^1y^4z^3");

	Polinom res = pol1 * pol2;
	res.printPair();

	return 0;
}
