// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_bst_ctor) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
}

TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(7);
    ASSERT_FALSE(tree.empty());
}

TEST(test_size) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.size(), 0);
    tree.insert(7);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1);
}

TEST(test_bst_cpy) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    ASSERT_EQUAL(*tree.max_element(), 3);
    BinarySearchTree<int> copyTree = BinarySearchTree<int>(tree);
    ASSERT_FALSE(copyTree.empty());
    ASSERT_EQUAL(copyTree.size(), 1);
    ASSERT_EQUAL(copyTree.height(), 1);
    ASSERT_EQUAL(*copyTree.max_element(), 3);
}

TEST(test_find) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    ASSERT_EQUAL(*tree.find(3), 3);
    tree.insert(7);
    tree.insert(5);
    tree.insert(1);
    ASSERT_EQUAL(*tree.find(5), 5);
    ASSERT_EQUAL(*tree.find(7), 7);
    ASSERT_EQUAL(*tree.find(1), 1);
}

TEST(test_height1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    ASSERT_EQUAL(tree.height(), 1);
    tree.insert(5);
    ASSERT_EQUAL(tree.height(), 2);
    tree.insert(3);
    ASSERT_EQUAL(tree.height(), 2);
}

TEST(test_height2) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    ASSERT_EQUAL(tree.height(), 1);
    tree.insert(5);
    ASSERT_EQUAL(tree.height(), 2);
    tree.insert(3);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(10);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(6);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(12);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(15);
    ASSERT_EQUAL(tree.height(), 4);
    tree.insert(11);
    ASSERT_EQUAL(tree.height(), 4);
}

/*TEST(test_inorder_preorder) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    tree.insert(7);
    tree.insert(6);
    ostringstream os;
    ostringstream os1;
    tree.traverse_inorder(os); // inorder, 134567
    ASSERT_EQUAL(os.str(), "1 3 4 5 6 7 ")
    tree.traverse_preorder(os1); // preorder, 531476
    ASSERT_EQUAL(os1.str(), "5 3 1 4 7 6 ")
}

TEST(test_preorder2) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(6);
    tree.insert(7);
    tree.insert(12);
    tree.insert(9);
    tree.insert(13);
    tree.traverse_preorder(cout); // preorder, 867 12 9 13
}*/

TEST(test_insert) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    ASSERT_EQUAL(tree.size(), 1);
    ASSERT_EQUAL(*tree.find(4), 4);
}

TEST(test_min_max) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(8);
    tree.insert(7);
    tree.insert(12);
    ASSERT_EQUAL(*tree.min_element(), 4);
    ASSERT_EQUAL(*tree.max_element(), 12);
    BinarySearchTree<int> tree1;
    tree1.insert(4);
    ASSERT_EQUAL(*tree1.min_element(), 4);
    ASSERT_EQUAL(*tree1.max_element(), 4);
}

TEST(test_min_greater_than) {
    BinarySearchTree<int> tree;
    tree.insert(12);
    tree.insert(7);
    tree.insert(11);
    tree.insert(5);
    tree.insert(6);
    tree.insert(33);
    ASSERT_EQUAL(*tree.min_greater_than(5), 6);
    ASSERT_EQUAL(*tree.min_greater_than(6), 7);
    ASSERT_EQUAL(*tree.min_greater_than(12), 33);
}

TEST(test_check_sort) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(16);
    tree.insert(7);
    tree.insert(11);
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(5);
    tree.insert(6);
    tree.insert(8);
    ASSERT_TRUE(tree.check_sorting_invariant());
}
TEST_MAIN()
