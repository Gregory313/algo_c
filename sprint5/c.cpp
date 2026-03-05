#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>


using namespace std;

string resultLR(const Node* root){
    if(!root) return "";
    return resultLR(root->left) + to_string(root->value) + resultLR(root->right);
}

string resultRL(const Node* root){
    if(!root) return "";
    return resultRL(root->right) + to_string(root->value) + resultRL(root->left);
}



bool Solution(const Node* root) {
    if(!root) return 0;
    return resultRL(root->right) == resultLR(root->left);
} 

#ifndef REMOTE_JUDGE
void test() {
    Node node1({3, nullptr, nullptr});
    Node node2({4, nullptr, nullptr});
    Node node3({4, nullptr, nullptr});
    Node node4({3, nullptr, nullptr});
    Node node5({2, &node1, &node2});
    Node node6({2, &node3, &node4});
    Node node7({1, &node5, &node6});
    assert(Solution(&node7));
}


int main() {
  test();
}
#endif