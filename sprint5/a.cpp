#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#include <algorithm>
#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;


int findMax(const Node* root){
    if(!root) return -2147483647;

    int left_v = findMax(root->left);
    int right_v = findMax(root->right);

    return std::max({root->value, left_v, right_v});
}


int Solution(const Node* root) {
    return findMax(root);
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, &node3, nullptr});
    assert(Solution(&node4) == 3);
}

int main() {
  test();
}
#endif