#pragma once
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <iostream>
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
	long get_credit(std::string str);
	std::unordered_map<std::string, long> get_map();

private:
	void process_tmp(const std::vector<Node>& tmp, Node& paing, std::unordered_map<std::string, long>& arrears);
};