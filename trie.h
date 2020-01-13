//
// Created by lenovo on 2019/12/26.
//

#ifndef QIC_TRIE_H
#define QIC_TRIE_H

#include "bits/stdc++.h"
using namespace std;

struct trie_node {
    map<int, int> position;
    int node_name, node_cnt, id;
    trie_node* father;
    trie_node* list_next;
    vector<trie_node*> child;
    trie_node() {
        father = nullptr;
        list_next = nullptr;
        node_name = -1;
        node_cnt = 0;
        id = 0;
    }
};

class trie {

public:
    trie_node* root;
    vector<int> degree;
    vector<trie_node*> linked_list;
    int node_size, id_cnt;
    trie(int node_size) {
        this->node_size = node_size;
        degree = vector<int>(node_size);
        root = new trie_node;
        linked_list = vector<trie_node*>(node_size);
    }

    void clear() {
        if (root == nullptr) {
            return;
        }
        for (auto x: root->child) {
            clear_node(x);
        }
        root->child.clear();
        root->position.clear();
        root->node_cnt = 0;
        linked_list.clear();
        linked_list = vector<trie_node*>(node_size);
    }

    void clear_node(trie_node* cur) {
        if (cur == nullptr) {
            return;
        }
        for (auto x: cur->child) {
            clear_node(x);
        }
    }

    void insert(const vector<int>& pattern) {
        trie_node* cur = root;
        for (int x: pattern) {
            if (cur->position.find(x) == cur->position.end()) {
                cur->position[x] = cur->child.size();
                cur->child.emplace_back(new trie_node);
                trie_node *next = cur->child[cur->child.size() - 1];
                next->father = cur;
                next->node_name = x;
                next->list_next = linked_list[x];
                linked_list[x] = next;
            }
            degree[x]++;
            int next_index = cur->position[x];
            cur = cur->child[next_index];
            cur->node_cnt++;
        }
    }

    void insert(const set<int>& pattern) {
        trie_node* cur = root;
        for (int x: pattern) {
            if (cur->position.find(x) == cur->position.end()) {
                cur->position[x] = cur->child.size();
                cur->child.emplace_back(new trie_node);
                trie_node *next = cur->child[cur->child.size() - 1];
                next->father = cur;
                next->node_name = x;
                next->list_next = linked_list[x];
                linked_list[x] = next;
            }
            degree[x]++;
            int next_index = cur->position[x];
            cur = cur->child[next_index];
            cur->node_cnt++;
        }
    }

    void pre_visit() {
        pre_visit(*root);
    }

    void pre_visit(trie_node node) {
        cout << node.node_name << endl;
        for (auto x: node.child) {
            pre_visit(*x);
        }
    }
};

#endif //QIC_TRIE_H
