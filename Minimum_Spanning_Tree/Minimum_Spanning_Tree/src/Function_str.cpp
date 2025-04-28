#include"Function_str.hpp"

std::vector<std::string> split(std::string str) {
		std::vector <std::string> str_vector{};
		char tmp = ' ';
		int j = 0;
		for (int i = 0; i <= str.size(); ++i) {
			if ((str[i] == tmp || i == str.size()) && j <= i) {
				str_vector.push_back(str.substr(j, i - j));
				j = i + 1;
			}
		}

		return str_vector;
}