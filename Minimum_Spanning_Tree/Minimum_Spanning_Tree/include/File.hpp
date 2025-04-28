#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "Position.hpp"



class File_Spanning_Tree final{
private:
	std::vector<Position<>> pos{};
	std::string s_fname {};

public:
	File_Spanning_Tree() = default;
	File_Spanning_Tree(const std::string &name);
	File_Spanning_Tree(const char* name);
	File_Spanning_Tree(const File_Spanning_Tree& file);
	~File_Spanning_Tree();

public:
	File_Spanning_Tree& operator = (const File_Spanning_Tree& tree);

public:
	void read();
	void read(const std::string &name);
	void write(const std::string& path);
	void write(const char* path);

public:
	void set_name(const std::string& name);

public:
	bool exist() const;

public:
	std::string get_filename() const;
	std::vector<Position<>> get_position() const;
};