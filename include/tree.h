// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct Node {
    char value;
    std::vector<Node*> children;

    explicit Node(char val) {
        value = val;
    }
};

class Tree {
 public:
    Node* root;

    explicit Tree(std::vector<char> in);
    ~Tree();

 private:
    void build(Node* current, std::vector<char> remaining);
    void destroy(Node* node);
};

typedef Tree PMTree;

std::vector<std::vector<char>> getAllPerms(Tree& tree);
std::vector<char> getPerm1(Tree& tree, int num);
std::vector<char> getPerm2(Tree& tree, int num);

#endif  // INCLUDE_TREE_H_
