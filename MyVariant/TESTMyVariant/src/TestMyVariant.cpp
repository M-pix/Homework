#include <gtest/gtest.h>
#include "MyVariant.hpp"

TEST(testMyVariant, get) {
	int a = 7;
	MyVariant<int, double, char> var(1);
	MyVariant<int, float, char> tmp(1.1f);
	MyVariant<int, float, char> str('h');
	size_t i = var.index();
	bool y = var.hold_alternative();
	a = var.get<int>();
	EXPECT_EQ(a, 1);
	EXPECT_EQ(tmp.get<float>() , 1.1f);
	EXPECT_EQ(tmp.get<char>(), 'h');

}

TEST(testMyVariant, hold_alternative) {
	int a = 7;
	MyVariant<int, double, char> var(1);
	MyVariant<double> tmp(double(1.1));
	EXPECT_EQ(var.hold_alternative(),true);
	EXPECT_EQ(tmp.hold_alternative(), false);
}

TEST(testMyVariant, index) {
	int a = 7;
	MyVariant<int, double, char> var(1);
	MyVariant<int, double, char> tmp(double(1.1));
	EXPECT_EQ(var.index() , 1);
	EXPECT_EQ(tmp.index(), 2);
}