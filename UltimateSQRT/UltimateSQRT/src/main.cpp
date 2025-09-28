#pragma once

#include <iostream>
#include "UltimateSQRT.hpp"
#include <vector>

int main()
{
	std::vector<double> Vector{ 10,12,32.1,323.3203 };
	std::vector<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	return 0;
}
