
#include <iostream>

#include "File.hpp"
#include "Minimum_Spanning_Tree.hpp"


int main()
{
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\Test_good.txt");
	std::vector<Position<>> pos = tree_2->get_position();
	Spanning_Tree* tree = new Spanning_Tree(pos);
	return 0;
}
