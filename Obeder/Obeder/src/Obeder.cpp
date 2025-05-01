#include"Obeder.hpp"

void Obeder::process_tmp(const std::vector<Node>& tmp, Node& paing, std::unordered_map<std::string, long>& arrears) {
	for (const auto& elem_1 : tmp) {
		if (elem_1.get_id() != paing.get_id()) {
			if (arrears.count(elem_1.get_id() + " " + paing.get_id())) {
				arrears[elem_1.get_id() + " " + paing.get_id()] += elem_1.get_sum();
			}
			else if (arrears.count(paing.get_id() + " " + elem_1.get_id())) {
				arrears[paing.get_id() + " " + elem_1.get_id()] -= elem_1.get_sum();
			}
			else {
				arrears[elem_1.get_id() + " " + paing.get_id()] = elem_1.get_sum();
			}
		}
	}
}

Obeder::Obeder(const std::vector<Node>& node) : Obeder(){
	if (node.empty()) return;
	std::string time = node[0].get_time();
	Node paing{};
	std::vector<Node> tmp{};
	for (const auto& elem : node) {
		if (elem.get_time() != time) {
			time = elem.get_time();
			process_tmp(tmp, paing, arrears);
			tmp.clear();
		}
		if (elem.get_sum() > 0)
			paing = elem;
		tmp.push_back(elem);

	}
	if (!tmp.empty()) {
		process_tmp(tmp, paing, arrears);
	}
}

Obeder::Obeder(const Obeder& obeder) : Obeder() {
	//Obeder tmp(obeder);
	//std::swap(tmp.arrears, arrears);
	//tmp.arrears.clear();
	arrears = obeder.arrears;
}

Obeder::~Obeder() {
	arrears.clear();
}

Obeder& Obeder::operator=(const Obeder& obeder) {
	if (this != &obeder) {
		//Obeder tmp(obeder);
		//std::swap(tmp.arrears, arrears);
		//tmp.arrears.clear();
		arrears = obeder.arrears;
	}
	return *this;
}

long Obeder::get_credit(std::string str) {
	try {
		long value = arrears.at(str);
		return value;
	}
	catch (const std::out_of_range& except) {
		std::cout << "Key not found: " << except.what() << std::endl;
	}

}

std::unordered_map<std::string, long> Obeder::get_map() {
	return arrears;
}