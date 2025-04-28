#include "Minimum_Spanning_Tree.hpp"
#include "Function_str.hpp"


namespace compare {
	bool f_compare(Position<std::string,float> one, Position<std::string, float> two) {
		 return one.second_vertex() < two.second_vertex();
	}
}


Spanning_Tree::Spanning_Tree(const std::vector<Position<>> &new_pos) {
	pos = new_pos;
	restruct_tree();
}

Spanning_Tree::~Spanning_Tree() {
	pos.clear();
}

Spanning_Tree& Spanning_Tree::operator = (const Spanning_Tree& tree) {
	if (&tree != this) {
		pos.clear();
		pos = tree.pos;
	}
	return *this;
}

float Spanning_Tree::distance ( Position<>& one, Position<>& two) const{
	float len = sqrt(pow((two.first_vertex() - one.first_vertex()), 2) + pow((two.second_vertex() - one.second_vertex()), 2));//
	return len;
}

void Spanning_Tree::restruct_tree() {
	for (int i =0;i<pos.size();++i)
		for (int j = 0; j < pos.size(); ++j){
			std::string str(std::to_string(j) + " " +std::to_string(i));
			Position<std::string, float> pair (str, distance(pos[i],pos[j]));
			path.insert(pair);
	}
	//std::sort(begin(path), end(path), compare::f_compare);//оптимизацией займись без сортировки кароче подумать unordered_set
	pos.clear();
	std::unordered_set<std::string> vertexes;
	std::set<Position<std::string,float>> tmp{};
	for (auto elem : path) {
		std::vector str = split(elem.first_vertex());
		if (!vertexes.contains(str[0]) || !vertexes.contains(str[1])) {
			vertexes.insert(str[0]);
			vertexes.insert(str[1]);
			tmp.insert(elem);
		}
	}
	path = tmp;
}

std::set<Position<std::string, float>> Spanning_Tree::get_path() const{
	return path;
}

