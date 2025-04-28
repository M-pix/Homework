#include"Obeder.hpp"

Obeder::Obeder(const std::vector<Node>& node) {
	std::string time = node[0].get_time();
	Node paing{};
	std::vector<Node> tmp{};
	for (const auto& elem : node) {
		if (elem.get_time() != time) {
			time = elem.get_time();
			for (const auto& elem_1 : tmp)
				if (arrears.count(elem_1.get_id() + " " + paing.get_id()) && (elem_1.get_id() != paing.get_id())) {
					arrears[elem_1.get_id() + " " + paing.get_id()] += elem_1.get_sum();
				}
				else if(arrears.count(paing.get_id() + " " + elem_1.get_id()) && (elem_1.get_id() != paing.get_id())) {
					arrears[elem_1.get_id() + " " + paing.get_id()] -= elem_1.get_sum();
				}
				else {
					arrears[elem_1.get_id() + " " + paing.get_id()] = elem_1.get_sum();
				}
		}
		else {
			if (elem.get_sum() > 0)
				paing = elem;
			tmp.push_back(elem);
		}

	}
}

Obeder::Obeder(const Obeder& obeder) {
	arrears = obeder.arrears;
}

Obeder& Obeder::operator=(const Obeder& obeder) {
	if (this != &obeder) {
		arrears = obeder.arrears;
	}
	return *this;
}