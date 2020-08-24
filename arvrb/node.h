#ifndef  NODE_H
#define  NODE_H
#include "item.h"
enum  Color {RED , BLACK};
//  Definition  of a node of the  tree
template  <typename  Tkey , typename  Tvalue>
class  Node {
    public:
        Tkey  key;
        Tvalue  value;
        Color  color;
        Node *left;
        Node *right;
        Node *parent;
};
#endif