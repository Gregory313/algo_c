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

void compEl(const Node* root, string& fin){
    if(!root) return;

    string left_s;
    compEl(root->left, left_s);

    string right_s;
    compEl(root->right, right_s);

    fin = left_s + to_string(root->value) + right_s;
}


bool Solution(const Node* root1, const Node* root2) {
    if(!root1 || !root2) return false;
    string s1, s2;
    
    compEl(root1, s1);
    compEl(root2, s2);

    if(s1 == s2){
        return true;
    }
    return false;

} 

#ifndef REMOTE_JUDGE
void test() {

    Node node1({1, nullptr, nullptr});
    Node node2({2, nullptr, nullptr});
    Node node3({3, &node1, &node2});

    Node node4({1, nullptr, nullptr});
    Node node5({2, nullptr, nullptr});
    Node node6({3, &node4, &node5});
    assert(Solution(&node3, &node6));
}

int main() {
  test();
}
#endif