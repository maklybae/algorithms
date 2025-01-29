#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <vector>

struct Node {
    Node(int t);
    std::vector<int> key;
    std::vector<Node*> children;
    Node* parent;
    bool isLeaf;
    int t;
};


class BTree {
public:
    explicit BTree(int t);

    ~BTree();

    void insert(int key);

    size_t size() const;

    int64_t sum() const;
    

private:
    Node* root;
    int t_;
    int size_;
};

#endif