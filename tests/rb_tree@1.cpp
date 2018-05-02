#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

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

TEST_CASE("deleting")
{
    	tree_t<int> tree{3, 4, 2, 1, 5, 10, 7, 8};    	
    	
	tree.remove(5);
    	std::string result5{"------10\n"
	                        "----------8\n"
                            "--------7\n"
                            "----4\n"
                            "--3\n"
                            "----2\n"
                            "------1\n"};
	    std::ostringstream ostream1;
	    tree.print(ostream1, tree.root(), 1);
	    REQUIRE( ostream1.str() == result5 );
	       
	    tree.remove(1);
    		std::string result1{"------10\n"
	                        "----------8\n"
                            "--------7\n"
                            "----4\n"
                            "--3\n"
                            "----2\n"};
	    std::ostringstream ostream2;
	    tree.print(ostream2, tree.root(), 1);
	    REQUIRE( ostream2.str() == result1 );
	
	tree_t<int> tree0{8, 3, 11, 1, 5, 9, 14, 6, 10, 12, 15, 7, 13};    	
    	
	tree0.remove(11);
    	std::string result11{"--------15\n"
	                    "------14\n"
                            "--------13\n"
                            "----12\n"
                            "--------10\n"
                            "------9\n"
                            "--8\n"
			    "----------7\n"
			    "--------6\n"
			    "------5\n"
			    "----3\n"
			    "------1\n"};
	    std::ostringstream ostream3;
	    tree.print(ostream3, tree0.root(), 1);
	    REQUIRE( ostream3.str() == result11 );
}
 
SCENARIO("BST delete non inserted element", "[delete]") {
    tree_t<int> tree{8};
    REQUIRE( !tree.remove(4) );
    REQUIRE( !tree.isEmpty() );
}
//                +----+
//                |-08-|                                               *
//                +----+
//
//
//                                          08
//                                         ---->
SCENARIO("BST delete root without children", "[delete]") {
    tree_t<int> tree{8};
    REQUIRE( tree.remove(8) );
    REQUIRE( tree.isEmpty() );
}
//                +----+                                              +----+
//                |-08-|                                              | 04 |
//                +----+                                              +----+
//                  /                                                   /
//                 /                                                   /
//           +----+                                              +----+
//           | 04 |                                              | 03 |
//           +----+                                              +----+
//             /
//            /
//      +----+                              08
//      | 03 |                             ---->
//      +----+
SCENARIO("BST delete root with one child", "[delete]") {
    tree_t<int> tree {8, 4, 3};
    REQUIRE( tree.remove(8) );
    REQUIRE( tree == tree_t<int>({4, 3}) );
}
//                +----+                                              +----+
//                |-08-|                                              | 09 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /          \
//            /         /  \                                      /            \
//      +----+    +----+    +----+          08              +----+              +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |              | 13 |
//      +----+    +----+    +----+                          +----+              +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 11 |
//                     +----+                                              +----+
//                        \                                                   \
//                         \                                                   \
//                          +----+                                              +----+
//                          | 12 |                                              | 12 |
//                          +----+                                              +----+
SCENARIO("BST delete root with children", "[delete]") {
    tree_t<int> tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(8) );
    REQUIRE( tree == tree_t<int>({9, 4, 3, 10, 13, 11, 12}) );
}
//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                                  /\
//            /         /  \                                                /  \
//      +----+    +----+    +----+          03                        +----+    +----+
//      |-03-|    | 09 |    | 13 |         ---->                      | 09 |    | 13 |
//      +----+    +----+    +----+                                    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 11 |
//                     +----+                                              +----+
//                        \                                                   \
//                         \                                                   \
//                          +----+                                              +----+
//                          | 12 |                                              | 12 |
//                          +----+                                              +----+
SCENARIO("BST delete non root without children", "[delete]") {
    tree_t<int> tree {8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(3) );
    REQUIRE( tree == tree_t<int>({8, 4, 10, 9, 13, 11, 12}) );
}
//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /         /\
//            /         /  \                                      /         /  \
//      +----+    +----+    +----+          11              +----+    +----+    +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |    | 09 |    | 13 |
//      +----+    +----+    +----+                          +----+    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     |-11-|                                              | 12 |
//                     +----+                                              +----+
//                        \
//                         \
//                          +----+
//                          | 12 |
//                          +----+
SCENARIO("BST delete non root with one child", "[delete]") {
    tree_t<int> tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(11) );
    REQUIRE( tree == tree_t<int>({8, 4, 3, 10, 9, 13, 12}) );
}
//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    |-10-|                                    | 04 |    | 11 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /         /\
//            /         /  \                                      /         /  \
//      +----+    +----+    +----+          10              +----+    +----+    +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |    | 09 |    | 13 |
//      +----+    +----+    +----+                          +----+    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 12 |
//                     +----+                                              +----+
//                        \
//                         \
//                          +----+
//                          | 12 |
//                          +----+
SCENARIO("BST delete non root with children", "[delete]") {
    tree_t<int> tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(10) );
    REQUIRE( tree == tree_t<int>({8, 4, 3, 11, 9, 13, 12}) );
}
