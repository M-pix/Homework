#include <gtest/gtest.h>
#include "File.hpp"


TEST(Test_file, Constructor) {
	File_Spanning_Tree* tree_1 = new File_Spanning_Tree();
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\Test_good.txt");
	//File_Spanning_Tree* tree_3 = new File_Spanning_Tree(tree_1);
}
TEST(Test_file, empty) {
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\empty.txt");
	//File_Spanning_Tree* tree_3 = new File_Spanning_Tree(tree_1);
}
TEST(Test_file, one_elem) {
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\one_elem.txt");
	//File_Spanning_Tree* tree_3 = new File_Spanning_Tree(tree_1);
}
TEST(Test_file, probel) {
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\probel.txt");
	//File_Spanning_Tree* tree_3 = new File_Spanning_Tree(tree_1);
}
TEST(Test_file, Test) {
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\Test.txt");
	//File_Spanning_Tree* tree_3 = new File_Spanning_Tree(tree_1);
}
TEST(Test_file, test_write) {
	File_Spanning_Tree* tree_2 = new File_Spanning_Tree("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\Test_good.txt");
	tree_2->write("C:\\Users\\deima\\Documents\\proga\\Minimum_Spanning_Tree\\TXT\\write_test.txt");
	//File_Spanning_Tree* tree_3 = new File_Spanning_Tree(tree_1);
}