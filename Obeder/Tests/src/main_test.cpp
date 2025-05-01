#include<gtest/gtest.h>
#include "File.hpp"
#include "Obeder.hpp"
#include "Str.hpp"

TEST(test_file, file) {
	File file("C:/Users/deima/Documents/proga/Obeder/TXT/test.txt");
	std::vector<long> tmp{ 3000, - 1100, - 900, - 600, - 1700, - 1200, 4000, - 800, 2300, - 1500 };
	for (int i = 0;i<10;++i) {
		
		EXPECT_EQ(file.get_position()[i].get_sum(), tmp[i]);
	}
	file.set_data_out(file.get_position());

	file.write("C:\\Users\\deima\\Documents\\proga\\Obeder\\TXT\\out.txt");
}

TEST(test_obeder, obeder) {
	File file("C:/Users/deima/Documents/proga/Obeder/TXT/test.txt");
	Obeder obed(file.get_position());
	std::vector<Node> tmp{};
	for (const auto& [key, value] : obed.get_map()) {
		Node node(split(key)[0], split(key)[1], value);
		tmp.push_back(node);
	}
}

int main() {
	return 0;
}