#include<iostream>
#include"rbtree.cpp"
int main(){
    RBTree tree = RBTree();

    tree.insert(5, "a");
    tree.insert(4, "b");
    tree.insert(6, "c");
    tree.insert(7, "d");
    tree.insert(8, "e");
    tree.insert(9, "f");
    tree.insert(10, "g");
    tree.insert(20, "h");
    tree.preorder();
    std::cout << "-----------------------------------" << std::endl;
    tree.remove(4);
    tree.remove(5);
    tree.preorder();
    std::cout << "-----------------------------------" << std::endl;
    tree.~RBTree();

    return 0;
}