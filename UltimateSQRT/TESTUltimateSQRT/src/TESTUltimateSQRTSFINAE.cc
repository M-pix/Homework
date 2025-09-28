#include <gtest/gtest.h>
#include <UltimateSQRTSFINAE.hpp>
#include <unordered_set>
#include <vector>
#include <set>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>

TEST(UltimateSQRT, SFINAEint_) {
	int elem = 9;
	int tmpElem = 9;
	ultimateSQRT(elem);
	EXPECT_EQ(std::sqrt(tmpElem), elem);
}

TEST(UltimateSQRT, SFINAEfloat_) {
	float elem = 9.1;
	float tmpElem = 9.1;
	ultimateSQRT(elem);
	EXPECT_EQ(std::sqrt(tmpElem), elem);
}

TEST(UltimateSQRT, SFINAEdouble_) {
	double elem = 9.0;
	double tmpElem = 9.0;
	ultimateSQRT(elem);
	EXPECT_EQ(std::sqrt(tmpElem), elem);
}

TEST(UltimateSQRT, SFINAEset_) {
	std::set<double> Set{ 10,12,32.1,323.3203 };
	std::set<double> tmpSet{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpSet);
	for (auto it = Set.begin(), it_ = tmpSet.begin(); it != Set.end(), it_ != tmpSet.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, SFINAEunordered_set_) {
	std::unordered_set<double> Set{ 10,12,32.1,323.3203 };
	std::unordered_set<double> tmpSet{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpSet);
	for (auto it = Set.begin(), it_ = tmpSet.begin(); it != Set.end(), it_ != tmpSet.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, SFINAEvector_) {
	std::vector<double> Vector{ 10,12,32.1,323.3203 };
	std::vector<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	for (auto it = Vector.begin(), it_ = tmpVector.begin(); it != Vector.end(), it_ != tmpVector.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, SFINAElist_) {
	std::list<double> Vector{ 10,12,32.1,323.3203 };
	std::list<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	for (auto it = Vector.begin(), it_ = tmpVector.begin(); it != Vector.end(), it_ != tmpVector.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, SFINAEforwardList_) {
	std::forward_list<double> Vector{ 10,12,32.1,323.3203 };
	std::forward_list<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	for (auto it = Vector.begin(), it_ = tmpVector.begin(); it != Vector.end(), it_ != tmpVector.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, SFINAEmap_) {
	std::map<double, double> Map{ {10,12 }, {32.1, 323.3203} };
	std::map<double, double> tmpMap{ {10,12 }, {32.1, 323.3203} };
	ultimateSQRT(tmpMap);
	for (auto it = Map.begin(), it_ = tmpMap.begin(); it != Map.end(), it_ != tmpMap.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt((*it).second), (*it_).second);
}

TEST(UltimateSQRT, SFINAEunordered_map_) {
	std::unordered_map<double, double> Map{ {10,12 }, {32.1, 323.3203} };
	std::unordered_map<double, double> tmpMap{ {10,12 }, {32.1, 323.3203} };
	ultimateSQRT(tmpMap);
	for (auto it = Map.begin(), it_ = tmpMap.begin(); it != Map.end(), it_ != tmpMap.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt((*it).second), (*it_).second);
}