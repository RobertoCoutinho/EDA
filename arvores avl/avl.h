#ifdef AVL_H
#define AVL_H
#include "item.h"
    struct node;
    Node* avl_insert(Node* node, Tkey key, Tvalue value);
    Node* avl_delete(Node* node, Tkey key);
    
    
#endif