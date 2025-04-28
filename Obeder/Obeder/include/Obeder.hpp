#pragma once
#include <unordered_map>
#include <string>
#include "Node.hpp"
class Obeder final{
private:
	std::unordered_map<std::string,long> arrears{};

public:
	Obeder() = default;
	Obeder(const std::vector<Node> &node);
	Obeder(const Obeder& obeder);
	~Obeder();

public:
	Obeder& operator = (const Obeder& obeder);

public:
	long get_credit();
};