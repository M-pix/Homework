#include <gtest/gtest.h>
#include <UltimateSQRT.hpp>
#include <unordered_set>
#include <vector>
#include <set>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <deque>

TEST(UltimateSQRT, int_) {
	int elem = 16;
	int tmpElem = 16;
	ultimateSQRT(elem);
	EXPECT_EQ(std::sqrt(tmpElem), elem);
}

TEST(UltimateSQRT, float_) {
	float elem = 9.1;
	float tmpElem = 9.1;
	ultimateSQRT(elem);
	EXPECT_EQ(std::sqrt(tmpElem), elem);
}

TEST(UltimateSQRT, double_) {
	double elem = 9.0;
	double tmpElem = 9.0;
	ultimateSQRT(elem);
	EXPECT_EQ(std::sqrt(tmpElem), elem);
}

TEST(UltimateSQRT, set_) {
	std::set<double> Set{ 10,12,32.1,323.3203 };
	std::set<double> tmpSet{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpSet);
	for (auto it = Set.begin(), it_ = tmpSet.begin(); it != Set.end(), it_ != tmpSet.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, unordered_set_) {
	std::unordered_set<double> Set{ 10,12,32.1,323.3203 };
	std::unordered_set<double> tmpSet{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpSet);
	for (auto it = Set.begin(), it_ = tmpSet.begin(); it != Set.end(), it_ != tmpSet.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, deque_) {
	std::deque<double> Deque{ 10,12,32.1,323.3203 };
	std::deque<double> tmpDeque{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpDeque);
	for (auto it = Deque.begin(), it_ = tmpDeque.begin(); it != Deque.end(), it_ != tmpDeque.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, vector_) {
	std::vector<double> Vector{ 10,12,32.1,323.3203 };
	std::vector<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	for (auto it = Vector.begin(), it_ = tmpVector.begin(); it != Vector.end(), it_ != tmpVector.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, list_) {
	std::list<double> Vector{ 10,12,32.1,323.3203 };
	std::list<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	for (auto it = Vector.begin(), it_ = tmpVector.begin(); it != Vector.end(), it_ != tmpVector.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, forwardList_) {
	std::forward_list<double> Vector{ 10,12,32.1,323.3203 };
	std::forward_list<double> tmpVector{ 10,12,32.1,323.3203 };
	ultimateSQRT(tmpVector);
	for (auto it = Vector.begin(), it_ = tmpVector.begin(); it != Vector.end(), it_ != tmpVector.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt(*it), *it_);
}

TEST(UltimateSQRT, map_) {
	std::map<double, double> Map{ {10,12 }, {32.1, 323.3203}};
	std::map<double, double> tmpMap{ {10,12 }, {32.1, 323.3203} };
	ultimateSQRT(tmpMap);
	for (auto it = Map.begin(), it_ = tmpMap.begin(); it != Map.end(), it_ != tmpMap.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt((*it).second), (*it_).second);
}

TEST(UltimateSQRT, unordered_map_) {
	std::unordered_map<double, double> Map{ {10,12 }, {32.1, 323.3203} };
	std::unordered_map<double, double> tmpMap{ {10,12 }, {32.1, 323.3203} };
	ultimateSQRT(tmpMap);
	for (auto it = Map.begin(), it_ = tmpMap.begin(); it != Map.end(), it_ != tmpMap.end(); ++it, ++it_)
		EXPECT_EQ(std::sqrt((*it).second), (*it_).second);
}