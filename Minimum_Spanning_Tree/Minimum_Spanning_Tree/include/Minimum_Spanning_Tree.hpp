#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <unordered_set>
#include "Position.hpp"

class Spanning_Tree final{

private:
	std::vector<Position<>> pos{};//std::string* str;
	std::set<Position<std::string,float>> path{};//мб уберем. не уберем

public:
	Spanning_Tree() = default;
	Spanning_Tree(const std::vector<Position<>> &pos);
	Spanning_Tree(const Spanning_Tree& tree);
	~Spanning_Tree();
	Spanning_Tree& operator = (const Spanning_Tree& tree);
	
private:
	float distance(Position<>& one, Position<>& two) const;	//считает расстояние между точками мб статик сделать
	void restruct_tree(); //строит последовательность точек

public:
	std::set<Position<std::string, float>> get_path() const;
};
