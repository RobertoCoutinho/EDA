#ifndef NODE
#define NODE

#include <vector>
#include "pessoa.h"
template <typename Tkey>

class Node
{
public:
    Tkey key;
    vector<Pessoas *> value;
    Node *left;
    Node *right;
    int height;
};

#endif