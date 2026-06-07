// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  <vector>
#include  "tree.h"

Tree::Tree(std::vector<char> in) {
    std::sort(in.begin(), in.end());
    root = new Node('*');
    build(root, in);
}

Tree::~Tree() {
    destroy(root);
}

void Tree::build(Node* current, std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }

    for (size_t i = 0; i < remaining.size(); ++i) {
        Node* child = new Node(remaining[i]);
        current->children.push_back(child);

        std::vector<char> next_remaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (i != j) {
                next_remaining.push_back(remaining[j]);
            }
        }

        build(child, next_remaining);
    }
}

void Tree::destroy(Node* node) {
    if (!node) return;
    for (size_t i = 0; i < node->children.size(); ++i) {
        destroy(node->children[i]);
    }
    delete node;
}

void dfsAll(Node* node, std::vector<char>& current_path,
            std::vector<std::vector<char>>& result) {
    if (node->children.empty()) {
        result.push_back(current_path);
        return;
    }

    for (size_t i = 0; i < node->children.size(); ++i) {
        current_path.push_back(node->children[i]->value);
        dfsAll(node->children[i], current_path, result);
        current_path.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(Tree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.root) return result;

    std::vector<char> path;
    dfsAll(tree.root, path, result);
    return result;
}

void dfs1(Node* node, std::vector<char>& path, int target,
          int& current_count, std::vector<char>& result) {
    if (!result.empty()) return;

    if (node->children.empty()) {
        current_count++;
        if (current_count == target) {
            result = path;
        }
        return;
    }

    for (size_t i = 0; i < node->children.size(); ++i) {
        path.push_back(node->children[i]->value);
        dfs1(node->children[i], path, target, current_count, result);
        path.pop_back();
    }
}

std::vector<char> getPerm1(Tree& tree, int num) {
    std::vector<char> result;
    int count = 0;
    std::vector<char> path;
    if (tree.root) {
        dfs1(tree.root, path, num, count, result);
    }
    return result;
}

int getFact(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

std::vector<char> getPerm2(Tree& tree, int num) {
    std::vector<char> result;
    if (!tree.root || tree.root->children.empty()) return result;

    int total_elements = tree.root->children.size();
    int max_perms = getFact(total_elements);

    if (num < 1 || num > max_perms) return result;

    int k = num - 1;
    Node* current = tree.root;

    while (!current->children.empty()) {
        int L = current->children.size();
        int branch_size = getFact(L - 1);

        int index = k / branch_size;
        k = k % branch_size;

        current = current->children[index];
        result.push_back(current->value);
    }
    return result;
}

