#include <iostream>
#include <queue>
#include "avl.h"
#include "item.h"
using std::cout;
using std::endl;

struct Node {
    Tkey key;
    Tvalue value;
    int height;
    Node *left;
    Node *right;
};

Tkey avl_getKey(Node *node) {
    return node->key;
}

Tvalue avl_getValue(Node *node) {
    return node->value;
}
