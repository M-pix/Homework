#include "Node.hpp"

Node::Node(std::string str_1, std::string str_2, long sum) :Node() {
	node = std::make_tuple(str_1, str_2, sum);
}

Node::Node(const std::tuple<std::string, std::string, long>& position) : Node() {
	node = position;
}

Node::Node(const Node& position) : Node() {
	node = position.node;
	//std::tuple<std::string,std::string,long> tmp = node;
	//Node tmp(position);
	//std::swap(tmp.node, node);
}


Node::Node(Node&& position) : Node() {
	node = position.node;
	//Node tmp(position);
	//std::swap(tmp.node, node);
}


Node& Node::operator =(const Node& position) {
	if (this != &position) {
		node = position.node;
		//Node tmp(position);
		//std::swap(tmp.node, node);
	}
	return *this;
}

std::string Node::get_time() const {
	return std::get<0>(node);
}
std::string Node::get_id() const{
	return std::get<1>(node);
}
long Node::get_sum() const{
	return std::get<2>(node);
}
