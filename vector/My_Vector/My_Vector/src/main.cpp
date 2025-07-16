// My_Vector.cpp : Defines the entry point for the application.
//
#pragma once

#include <iostream>
#include "My_vector.hpp"

using namespace std;

int main()
{
	My_vector<int> vector{ 4 };
	My_vector<int> vector_1(9,0,34);
	vector.push_back(6);
	vector.push_back(6);
	vector.push_back(6);
	vector = vector_1;
	return 0;
}
