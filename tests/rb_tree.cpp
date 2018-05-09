#include <catch.hpp>
#include <sstream>

#include "rb_tree.hpp"

TEST_CASE("creating tree")
{
    tree_t <int> tree;
    REQUIRE(tree.root() == nullptr);
}

TEST_CASE("insert and print tree int")
{
    tree_t <int> tree;

    std::string input1{ "+3\n" };
    std::string input2{ "+4\n" };
    std::string input3{ "+2\n" };
    std::string input4{ "+1\n" };
    std::string input5{ "+5\n" };
    std::string result{ "------5\n"
                        "----4\n"
                        "--3\n"
                        "----2\n"
                        "------1\n" };

    std::istringstream inp1{ input1 };
    std::istringstream inp2{ input2 };
    std::istringstream inp3{ input3 };
    std::istringstream inp4{ input4 };
    std::istringstream inp5{ input5 };

    REQUIRE(read(tree, inp1));
    REQUIRE(read(tree, inp2));
    REQUIRE(read(tree, inp3));
    REQUIRE(read(tree, inp4));
    REQUIRE(read(tree, inp5));

    std::ostringstream ostream;
    tree.print(ostream, tree.root(), 1);
    REQUIRE(ostream.str() == result);
}

TEST_CASE("insert and print tree double")
{
    tree_t <double> tree;

    std::string input1{ "+3.3\n" };
    std::string input2{ "+4.4\n" };
    std::string input3{ "+2.2\n" };
    std::string input4{ "+1.1\n" };
    std::string input5{ "+5.5\n" };
    std::string result{ "------5.5\n"
                        "----4.4\n"
                        "--3.3\n"
                        "----2.2\n"
                        "------1.1\n" };

    std::istringstream inp1{ input1 };
    std::istringstream inp2{ input2 };
    std::istringstream inp3{ input3 };
    std::istringstream inp4{ input4 };
    std::istringstream inp5{ input5 };

    REQUIRE(read(tree, inp1));
    REQUIRE(read(tree, inp2));
    REQUIRE(read(tree, inp3));
    REQUIRE(read(tree, inp4));
    REQUIRE(read(tree, inp5));

    std::ostringstream ostream;
    tree.print(ostream, tree.root(), 1);
    REQUIRE(ostream.str() == result);
}

TEST_CASE("find tree int")
{
    tree_t <int> tree;

    std::string input1{ "+3\n" };
    std::string input2{ "+4\n" };
    std::string input3{ "+2\n" };
    std::string input4{ "+1\n" };
    std::string input5{ "+5\n" };

    std::istringstream inp1{ input1 };
    std::istringstream inp2{ input2 };
    std::istringstream inp3{ input3 };
    std::istringstream inp4{ input4 };
    std::istringstream inp5{ input5 };

    REQUIRE(read(tree, inp1));
    REQUIRE(read(tree, inp2));
    REQUIRE(read(tree, inp3));
    REQUIRE(read(tree, inp4));
    REQUIRE(read(tree, inp5));

    REQUIRE(tree.find(1) == true);
    REQUIRE(tree.find(2) == true);
    REQUIRE(tree.find(5) == true);
    REQUIRE(tree.find(7) == false);
    REQUIRE(tree.find(0) == false);
}

TEST_CASE("find tree double")
{
    tree_t <double> tree;

    std::string input1{ "+3.3\n" };
    std::string input2{ "+4.4\n" };
    std::string input3{ "+2.2\n" };
    std::string input4{ "+1.1\n" };
    std::string input5{ "+5.5\n" };

    std::istringstream inp1{ input1 };
    std::istringstream inp2{ input2 };
    std::istringstream inp3{ input3 };
    std::istringstream inp4{ input4 };
    std::istringstream inp5{ input5 };

    REQUIRE(read(tree, inp1));
    REQUIRE(read(tree, inp2));
    REQUIRE(read(tree, inp3));
    REQUIRE(read(tree, inp4));
    REQUIRE(read(tree, inp5));

    REQUIRE(tree.find(1.1) == true);
    REQUIRE(tree.find(2.2) == true);
    REQUIRE(tree.find(5.5) == true);
    REQUIRE(tree.find(7.7) == false);
    REQUIRE(tree.find(0) == false);
}

TEST_CASE("equal")
{
	tree_t<int> tree1;
	tree_t<int> tree2 {3 , 4 , 2 , 1 , 5};
	tree1.insert(3);
	tree1.insert(4);
	tree1.insert(2);
	tree1.insert(1);
	tree1.insert(5);
	REQUIRE(tree1==tree2);
}

TEST_CASE("new0")
{
	tree_t<int> tree {10 , 85 , 15};
	
	std::string result{	"----85\n"
                        	"--15\n"
                        	"----10\n"};
	
	std::ostringstream ostream;
    	tree.print(ostream, tree.root(), 1);
    	REQUIRE(ostream.str() == result);
}

TEST_CASE("new")
{
	tree_t<int> tree {10 , 85 , 15 , 70 , 20 , 60 , 30 , 50 , 65 , 80 , 90 , 40 , 5 , 55};
	
	std::string result{	"--------90\n"
                        	"------85\n"
                        	"--------80\n"
                        	"----70\n"
                        	"--------65\n"
			  	"------60\n"
			  	"----------55\n"
			  	"--------50\n"
			  	"----------40\n"
			  	"--30\n"
			  	"------20\n"
			  	"----15\n"
			  	"------10\n"
			  	"--------5\n"};
	
	std::ostringstream ostream;
    	tree.print(ostream, tree.root(), 1);
    	REQUIRE(ostream.str() == result);
}






TEST_CASE("balance_1")
{
    tree_t<int> tree {3 ,2 , 1 };
	std::string out {
		"----3\n"
		"--2\n"
		"----1\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("balance_2")
{
    tree_t<int> tree{5 , 3 , 6 , 8 , 9 , 10 , 12 , 13};
	std::string out {
		"--------13\n"
		"------12\n"
		"----10\n"
		"------9\n"
		"--8\n"
		"------6\n"
		"----5\n"
		"------3\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("balance_3")
{
    tree_t<int> tree {1, 2 , 3 , 4 , 5 };

	std::string out {
		"------5\n"
		"----4\n"
		"------3\n"
		"--2\n"
		"----1\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("balance_4")
{
    tree_t<int> tree {10 , 85 , 15 , 70 , 20 , 60 , 30 , 50 ,65 ,80 ,90 ,40 , 5 ,55 };
	
	std::string out {
		
		"--------90\n"
		"------85\n"
		"--------80\n"
		"----70\n"
		"--------65\n"
		"------60\n"
		"----------55\n"
		"--------50\n"
		"----------40\n"
		"--30\n"
		"------20\n"
		"----15\n"
		"------10\n"
		"--------5\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_1")
{
    tree_t<int> tree {1 , 2 , 3 ,4 ,5};
	
	tree.remove(4);
	
	std::string out {
		
		"----5\n"
		"------3\n"
		"--2\n"
		"----1\n"
	};
	
	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_2")
{
    tree_t<int> tree {7,3,8,9,1,0};
	
	tree.remove(1);
	
	std::string out {
		"------9\n"
		"----8\n"
		"--7\n"
		"----3\n"
		"------0\n"
	};
	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_when_brother_is_black_and_his_right_son_is_red")
{
    tree_t<int> tree{1,2,3,4,5,6,7,8,9,10,11,0};
	
	
	tree.remove(3);
	tree.remove(2);
	
	std::string out {
		"--------11\n"
		"------10\n"
		"--------9\n"
		"----8\n"
		"------7\n"
		"--6\n"
		"------5\n"
		"----4\n"
		"------1\n"
		"--------0\n"
		
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_when_brother_is_black_and_his_sons")
{
    tree_t<int> tree{5 , 3 , 7 ,8 };
	
	tree.remove(8);
	tree.remove(3);
	
	std::string out {
		"----7\n"
		"--5\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_when_brother_is_red")
{
    tree_t<int> tree{5,3,7,8,6,2,1,9};
	
	
	tree.remove(2);
	
	std::string out {
		"--------9\n"
		"------8\n"
		"----7\n"
		"------6\n"
		"--5\n"
		"----3\n"
		"------1\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root(), 1);
	
	REQUIRE(ostream.str() == out);
}
