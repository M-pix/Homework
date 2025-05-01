
#include <iostream>
#include "Obeder.hpp"
#include "File.hpp"
#include "Str.hpp"

int main()
{
	File file("C:/Users/deima/Documents/proga/Obeder/TXT/test.txt");
	Obeder obed(file.get_position());
	std::vector<Node> tmp{};
	for (const auto& [key, value] : obed.get_map()) {
		Node node(split(key)[0], split(key)[1], value);
		tmp.push_back(node);
	}
	file.set_data_out(tmp);
	file.write("C:\\Users\\deima\\Documents\\proga\\Obeder\\TXT\\out.txt");
	return 0;
}
