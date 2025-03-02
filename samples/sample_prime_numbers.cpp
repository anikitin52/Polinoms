#include <iostream>
#include "Polinom.h"
#include <string>

int main()
{
	Polinom pol1("-3.1x^1y^1z^2-14.3x^1y^4z^3");
	Polinom pol2("-3.1x^1y^1z^2+1.3x^3y^8z^0");
	(pol1 * pol2).print();

	return 0;
}
