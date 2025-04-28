#include "File.hpp"
#include "Function_str.hpp"


namespace function_int {
	int len(int x) {
		int len = 0;
		while (x > 0) {
			x /= 10;
			len += 1;
		}
		return len;
	}
}


File_Spanning_Tree::File_Spanning_Tree(const std::string &name) : File_Spanning_Tree(){
	s_fname = name;
	read(name);
}

File_Spanning_Tree::File_Spanning_Tree(const char* name) : File_Spanning_Tree(){
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

File_Spanning_Tree::File_Spanning_Tree(const File_Spanning_Tree& file) :File_Spanning_Tree() {
	s_fname = file.s_fname;
	pos = file.pos;
}

File_Spanning_Tree::~File_Spanning_Tree() {
	pos.clear();
}

File_Spanning_Tree& File_Spanning_Tree::operator = (const File_Spanning_Tree& tree) {
	if (this != &tree) {
		pos = tree.pos;
		s_fname = tree.s_fname;
	}
	return *this;
}
void File_Spanning_Tree::read() {
	int x, y;
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
			x = std::atoi(tmp_vector[1].c_str());
			y = std::atoi(tmp_vector[2].c_str());
			if (function_int::len(x) < tmp_vector[1].length() || function_int::len(y) < tmp_vector[2].length())
				throw "Invalid non correct number";
			pos.push_back(Position(x, y));
		}
		read.close();
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

void File_Spanning_Tree::read(const std::string& path) {
	int x, y;
	std::string tmp_str{};
	std::vector<std::string>tmp_vector{};
	std::ifstream read;
	read.open(path);
	try {
		if (!read.is_open())
			throw "Invalid open file";
		while (std::getline(read, tmp_str)) { 
			tmp_vector = split(tmp_str);
			if (tmp_vector.size() != 3)
				throw "Invalid size str";
			x = std::atoi(tmp_vector[1].c_str());
			y = std::atoi(tmp_vector[2].c_str());
			if (function_int::len(x) < tmp_vector[1].length() || function_int::len(y) < tmp_vector[2].length())
				throw "Invalid non correct number";
			pos.push_back(Position(x, y));
		}
		read.close();
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

void File_Spanning_Tree::write(const std::string &path) {
	std::ofstream write;
	write.open(path);
	if (write.is_open())
	{
		while (pos.size()>0)
		{
			Position tmp = pos.back();
			write << tmp.first_vertex() <<" "<< tmp.second_vertex()<<std::endl;
			pos.pop_back();
		}
	}
	write.close();
}

void File_Spanning_Tree::write(const char* path) {
	std::ofstream write;
	write.open(path);
	if (write.is_open())
	{
		while (pos.size() > 0){
			Position tmp = pos.back();
			write << tmp.first_vertex() << " " << tmp.second_vertex() << std::endl;
			pos.pop_back();
		}
	}
	write.close();
}

bool File_Spanning_Tree::exist() const {
	try {
		if (s_fname.size()==0) {
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

std::string File_Spanning_Tree::get_filename() const{
	return s_fname;
}

std::vector<Position<>> File_Spanning_Tree::get_position() const{
	return pos;
}
void File_Spanning_Tree::set_name(const std::string& name) {
	s_fname = name;
}
