#pragma once
#include <string>
#include <utility>
#include <tuple>
#include <variant>


class Node final {

private:	
	std::tuple<std::string, std::string, long> node{};

public:
	Node() = default;
	Node(std::string str_1, std::string str_2, long sum);
	Node(const std::tuple<std::string, std::string, long>& position);
	Node(const Node& position);
	Node( Node&& position);

public:
	Node& operator = (const Node& position);

public:
	std::string get_time() const;
	std::string get_id() const;
	long get_sum() const;
};


