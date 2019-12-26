//
// Created by lenovo on 2019/12/26.
//

#ifndef QIC_TRIE_H
#define QIC_TRIE_H

#include "bits/stdc++.h"
using namespace std;

struct trie_node {
    bool isLeaf;
    map<int, int> position;
    vector<trie_node*> child;
    trie_node(): isLeaf(false) {
        child.clear();
    }
};

class trie {
public:
};

#endif //QIC_TRIE_H
