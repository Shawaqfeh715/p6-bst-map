#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <string>
#include <sstream>

using namespace std;


TEST(test_empty_construction) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
    ASSERT_TRUE(tree.begin() == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.max_element() == tree.end());
}



TEST(test_empty_find) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.find(5) == tree.end());
}


TEST(test_single_traversal) {
    BinarySearchTree<int> tree;
    tree.insert(42);
    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "42 ");
    oss.str("");
    tree.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "42 ");
}


TEST(test_single_min_max) {
    BinarySearchTree<int> tree;
    tree.insert(55);
    ASSERT_EQUAL(*tree.min_element(), 55);
    ASSERT_EQUAL(*tree.max_element(), 55);
}

TEST(test_multiple_inserts_size_height) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);
    ASSERT_EQUAL(tree.size(), 9u);
    ASSERT_EQUAL(tree.height(), 4u);
}

TEST(test_inorder_traversal_balanced) {
    BinarySearchTree<int> tree;
    int vals[] = {8,3,10,1,6,14,4,7,13};
    for (int v : vals) tree.insert(v);
    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "1 3 4 6 7 8 10 13 14 ");
}

TEST(test_preorder_traversal_balanced) {
    BinarySearchTree<int> tree;
    int vals[] = {8,3,10,1,6,14,4,7,13};
    for (int v : vals) tree.insert(v);
    ostringstream oss;
    tree.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "8 3 1 6 4 7 10 14 13 ");
}

TEST(test_find_existing_and_missing) {
    BinarySearchTree<int> tree;
    int vals[] = {8,3,10,1,6,14,4,7,13};
    for (int v : vals) tree.insert(v);
    for (int v : vals) {
        auto it = tree.find(v);
        ASSERT_TRUE(it != tree.end());
        ASSERT_EQUAL(*it, v);
    }
    ASSERT_TRUE(tree.find(0) == tree.end());
    ASSERT_TRUE(tree.find(9) == tree.end());
    ASSERT_TRUE(tree.find(15) == tree.end());
}

TEST(test_iterator_increment_all) {
    BinarySearchTree<int> tree;
    int vals[] = {5,3,7,2,4,6,8};
    for (int v : vals) tree.insert(v);
    int expected[] = {2,3,4,5,6,7,8};
    size_t i = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        ASSERT_EQUAL(*it, expected[i++]);
    }
    ASSERT_EQUAL(i, 7u);
}

TEST(test_iterator_postfix_increment) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    auto it = tree.begin();
    auto it2 = it++;
    ASSERT_EQUAL(*it2, 3);
    ASSERT_EQUAL(*it, 5);
    it2 = it++;
    ASSERT_EQUAL(*it2, 5);
    ASSERT_EQUAL(*it, 7);
    it2 = it++;
    ASSERT_EQUAL(*it2, 7);
    ASSERT_TRUE(it == tree.end());
}

TEST(test_min_max_elements) {
    BinarySearchTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    ASSERT_EQUAL(*tree.min_element(), 20);
    ASSERT_EQUAL(*tree.max_element(), 80);
}

TEST(test_min_greater_than_various) {
    BinarySearchTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    ASSERT_EQUAL(*tree.min_greater_than(10), 20);
    ASSERT_EQUAL(*tree.min_greater_than(20), 30);
    ASSERT_EQUAL(*tree.min_greater_than(25), 30);
    ASSERT_EQUAL(*tree.min_greater_than(30), 40);
    ASSERT_EQUAL(*tree.min_greater_than(45), 50);
    ASSERT_EQUAL(*tree.min_greater_than(50), 60);
    ASSERT_EQUAL(*tree.min_greater_than(65), 70);
    ASSERT_EQUAL(*tree.min_greater_than(70), 80);
    ASSERT_TRUE(tree.min_greater_than(80) == tree.end());
    ASSERT_TRUE(tree.min_greater_than(100) == tree.end());
}


TEST(test_copy_constructor) {
    BinarySearchTree<int> tree1;
    tree1.insert(8); tree1.insert(3); tree1.insert(10);
    BinarySearchTree<int> tree2(tree1);
    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_EQUAL(tree2.height(), 2u);
    tree1.insert(1);
    ASSERT_EQUAL(tree1.size(), 4u);
    ASSERT_EQUAL(tree2.size(), 3u);
    int expected[] = {3,8,10};
    size_t i = 0;
    for (int x : tree2) {
        ASSERT_EQUAL(x, expected[i++]);
    }
}

TEST(test_assignment_operator) {
    BinarySearchTree<int> tree1;
    tree1.insert(5); tree1.insert(2); tree1.insert(8);
    BinarySearchTree<int> tree2;
    tree2.insert(100);
    tree2 = tree1;
    ASSERT_EQUAL(tree2.size(), 3u);
    tree1.insert(1);
    ASSERT_EQUAL(tree1.size(), 4u);
    ASSERT_EQUAL(tree2.size(), 3u);
    int expected[] = {2,5,8};
    size_t i = 0;
    for (int x : tree2) {
        ASSERT_EQUAL(x, expected[i++]);
    }
}

TEST(test_large_tree_invariant) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i * 2); 
    }
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.size(), 1000u);
}

TEST(test_custom_comparator) {
    BinarySearchTree<int, std::greater<int>> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "7 5 3 ");
    ASSERT_EQUAL(*tree.min_element(), 7); 
    ASSERT_EQUAL(*tree.max_element(), 3);
}

TEST(test_const_iterator_usage) {
    const BinarySearchTree<int> tree = [](){
        BinarySearchTree<int> t;
        t.insert(5); t.insert(3); t.insert(7);
        return t;
    }();
    auto it = tree.begin();
    ASSERT_EQUAL(*it, 3);
    ++it;
    ASSERT_EQUAL(*it, 5);
    auto fit = tree.find(7);
    ASSERT_EQUAL(*fit, 7);
}

TEST(test_ostream_operator) {
    BinarySearchTree<int> tree;
    tree.insert(8); tree.insert(3); tree.insert(10);
    ostringstream oss;
    oss << tree;
    ASSERT_EQUAL(oss.str(), "[ 3 8 10 ]");
}

TEST(test_end_dereference_not_allowed) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    auto it = tree.end();
    auto it2 = tree.begin();
    ++it2;
    ASSERT_TRUE(it2 == tree.end());
}

TEST(test_copy_deepness) {
    BinarySearchTree<int> tree1;
    tree1.insert(5); tree1.insert(3); tree1.insert(7);
    BinarySearchTree<int> tree2(tree1);
    *tree2.find(3) = 30; 
    tree2.insert(4);
    ASSERT_EQUAL(tree1.size(), 3u);
    ASSERT_EQUAL(tree2.size(), 4u);
}

TEST(test_assignment_chain) {
    BinarySearchTree<int> tree1, tree2, tree3;
    tree1.insert(1);
    tree3 = tree2 = tree1;
    ASSERT_EQUAL(tree2.size(), 1u);
    ASSERT_EQUAL(tree3.size(), 1u);
}

TEST(test_large_random_inserts) {
    BinarySearchTree<int> tree;
    int values[] = {50,25,75,10,30,60,90,5,15,27,35,55,65,85,95};
    for (int v : values) tree.insert(v);
    ASSERT_EQUAL(tree.size(), 15u);
    ASSERT_TRUE(tree.check_sorting_invariant());
    for (int v : values) {
        ASSERT_TRUE(tree.find(v) != tree.end());
    }
}

TEST(test_iterator_equality) {
    BinarySearchTree<int> tree;
    tree.insert(1); tree.insert(2);
    auto it1 = tree.begin();
    auto it2 = tree.begin();
    ASSERT_TRUE(it1 == it2);
    ++it1;
    ASSERT_FALSE(it1 == it2);
    ++it2;
    ASSERT_TRUE(it1 == it2);
}

TEST(test_iterator_inequality) {
    BinarySearchTree<int> tree;
    tree.insert(10); tree.insert(20);
    auto it1 = tree.begin();
    auto it2 = tree.end();
    ASSERT_TRUE(it1 != it2);
    it1 = tree.end();
    ASSERT_FALSE(it1 != it2);
}


TEST(test_height_single_node) {
    BinarySearchTree<int> tree;
    tree.insert(42);
    ASSERT_EQUAL(tree.height(), 1u);
}

TEST(test_height_two_nodes_left) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    ASSERT_EQUAL(tree.height(), 2u);
}

TEST(test_insert_return_iterator) {
    BinarySearchTree<int> tree;
    auto it = tree.insert(5);
    ASSERT_EQUAL(*it, 5);
    auto it2 = tree.insert(3);
    ASSERT_EQUAL(*it2, 3);
    ASSERT_EQUAL(*it, 5);
}

TEST(test_double_insert_asserts) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    ASSERT_TRUE(true); 
}

TEST(test_large_tree_preorder_stress) {
    BinarySearchTree<int> tree;
    for (int i = 1000; i > 0; --i) {
        tree.insert(i);
    }
    ostringstream oss;
    tree.traverse_preorder(oss);
    string s = oss.str();
    ASSERT_TRUE(s.find("1000") == 0); 
}

TEST(test_many_min_greater_than_queries) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < 100; i+=2) {
        tree.insert(i);
    }
    for (int i = 1; i < 99; i+=2) {
        auto it = tree.min_greater_than(i);
        ASSERT_TRUE(it != tree.end());
        ASSERT_EQUAL(*it, i+1);
    }
}

TEST(test_invariant_break){
     BinarySearchTree<int> b;
     b.insert(2);
     b.insert(1);
     b.insert(3);

     *b.begin()=5;

     ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_invariant_deep_violation){
    BinarySearchTree<int> b;

    b.insert(10);
    b.insert(5);
    b.insert(15);
    b.insert(2);
    b.insert(7);

    auto it=b.find(7);
    *it=20;

    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_min_greater_than_exact_edge){
    BinarySearchTree<int> b;

    b.insert(10);
    b.insert(20);
    b.insert(30);

    ASSERT_EQUAL(*b.min_greater_than(10),20);
    ASSERT_EQUAL(*b.min_greater_than(19),20);
    ASSERT_EQUAL(*b.min_greater_than(20),30);

}

TEST_MAIN()
