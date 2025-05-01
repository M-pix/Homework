#include "File.hpp"
#include "Str.hpp"
#include "Node.hpp"

namespace function {
	int len(int x) {
		int len = 0;
		if (x < 0) {
			len += 1;
			x = abs(x);
		}
		while (x > 0) {
			x /= 10;
			len += 1;
		}
		return len;
	}
}

File::File(const std::string& name) : File() {
	s_fname = name;
	read(name);
}

File::File(const char* name) : File() {
	try {
		if (name == nullptr)
			throw "Invalid name is nullptr";// empty
		s_fname = name;
		std::string str(name);
		read(str);
		//size_file = pos.size();
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

File::File(const File& file) :File() {
	s_fname = file.s_fname;
	node = file.node;
	str_node = file.str_node;
}

File::~File() {
	node.clear();
	str_node.clear();
}

File& File::operator = (const File& file) {
	if (this != &file) {
		node = file.node;
		s_fname = file.s_fname;
	}
	return *this;
}
void File::read() {
	std::string x;
	std::string y;
	long z;
	std::string tmp_str{};
	std::vector<std::string>tmp_vector{};
	std::ifstream read;
	read.open(s_fname);
	try {
		if (!read.is_open())
			throw "Invalid open file";
		while (std::getline(read, tmp_str)) { //(read >> pos_ >> x >> y)//std::getline(read,tmp_str))
			tmp_vector = split(tmp_str);
			if (tmp_vector.size() != 3)
				throw "Invalid size str";
			x = tmp_vector[0];
			y = tmp_vector[1];
			z = std::atoi(tmp_vector[2].c_str());
			if (function::len(z) < tmp_vector[2].length())
				throw "Invalid non correct number";
			node.push_back(Node(x, y, z));
		}
		read.close();
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

void File::read(const std::string& path) {
	std::string x;
	std::string y;
	long z;
	std::string tmp_str{};
	std::vector<std::string>tmp_vector{};
	std::ifstream read;
	read.open(path);
	try {
		if (!read.is_open())
			throw "Invalid open file";
		while (std::getline(read, tmp_str)) { //(read >> pos_ >> x >> y)//std::getline(read,tmp_str))
			tmp_vector = split(tmp_str);
			if (tmp_vector.size() != 3)
				throw "Invalid size str";
			x = tmp_vector[0];
			y = tmp_vector[1];
			z = std::atoi(tmp_vector[2].c_str());
			if (function::len(z) < tmp_vector[2].length())
				throw "Invalid non correct number";
			node.push_back(Node(x, y, z));
		}
		read.close();
		read.close();
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

void File::write(const std::string& path) {
	std::ofstream write;
	write.open(path);
	if (write.is_open())
	{
		while (str_node.size() > 0)
		{
			Node tmp = str_node.back();
			write << tmp.get_time() << " " << tmp.get_id() << " " << tmp.get_sum() << std::endl;
			str_node.pop_back();
		}
	}
	write.close();
}

void File::write(const char* path) {
	std::ofstream write;
	write.open(path);
	if (write.is_open())
	{
		while (str_node.size() > 0) {
			Node tmp = str_node.back();
			write << tmp.get_time() << " " << tmp.get_id() << " " << tmp.get_sum() << std::endl;
			str_node.pop_back();
		}
	}
	write.close();
}

bool File::exist() const {
	try {
		if (s_fname.size() == 0) {
			throw "Invalid filename";
		}
		std::ifstream file(s_fname);
		if (file.is_open()) {
			return true;
		}
		else {
			throw "Invalid filename";
		}
	}
	catch (const char* error_message) {
		std::cout << error_message;
		return false;
	}
}

void File::set_data_out(std::vector<Node> data) {
	str_node = data; 
}

std::string File::get_filename() const {
	return s_fname;
}

std::vector<Node> File::get_position() const {
	return node;
}

void File::set_name(const std::string& name) {
	s_fname = name;
}
