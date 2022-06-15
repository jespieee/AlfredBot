// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_bst_ctor) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
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

TEST_MAIN()
