#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "Node.hpp"


class File final {
private:
	std::vector<Node> node{};
	std::vector<Node> str_node{};
	std::string s_fname{};

public:
	File() = default;
	File(const std::string& name);
	File(const char* name);
	File(const File& file);
	~File();

public:
	File& operator = (const File& tree);

public:
	void read();
	void read(const std::string& name);
	void write(const std::string& path);
	void write(const char* path);

public:
	void set_name(const std::string& name);

public:
	bool exist() const;

public:
	void set_data_out(std::vector<Node> data);
public:
	std::string get_filename() const;
	std::vector<Node> get_position() const;
};