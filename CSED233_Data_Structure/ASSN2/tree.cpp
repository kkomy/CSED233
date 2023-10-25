#include "tree.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string traversal;
  traversal = {};
  char ch_value = node_value + 48;

  BinaryTree left_tree;
  BinaryTree right_tree;
  Node *temp = NULL;
  find_node(&temp, _root, ch_value);
  if (temp == NULL) {
    traversal += "error";
    return traversal;
  }
  left_tree._root = temp->left;
  right_tree._root = temp->right;
  traversal += temp->value;
  traversal += " ";
  if (temp->left != NULL) {
    traversal += left_tree.pre_out();
  }
  if (temp->right != NULL) {
    traversal += right_tree.pre_out();
  }
    traversal.pop_back();
  return traversal;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string traversal;
  traversal = {};
  char ch_value = node_value + 48;

  BinaryTree left_tree;
  BinaryTree right_tree;
  Node *temp = NULL;
  find_node(&temp, _root, ch_value);
  if (temp == NULL) {
    traversal += "error";
    return traversal;
  }
  left_tree._root = temp->left;
  right_tree._root = temp->right;

  if (temp->left != NULL) {
    traversal += left_tree.post_out();
  }
  if (temp->right != NULL) {
    traversal += right_tree.post_out();
  }
  traversal += temp->value;
    traversal.pop_back();
  return traversal;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string traversal;
  traversal = {};
  char ch_value = node_value + 48;

  BinaryTree left_tree;
  BinaryTree right_tree;
  Node *temp = NULL;
  find_node(&temp, _root, ch_value);
  if (temp == NULL) {
    traversal += "error";
    return traversal;
  }

  left_tree._root = temp->left;
  right_tree._root = temp->right;

  if (temp->left != NULL) {
    traversal += left_tree.in_out();
  }
  traversal += temp->value;
  traversal += " ";
  if (temp->right != NULL) {
    traversal += right_tree.in_out();
  }
    traversal.pop_back();
  return traversal;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  char ch_value = node_value + 48;
  int depth = 0;
  Node *goal;
  find_node(&goal, _root, ch_value);
  Node *temp;
  BinaryTree left_tree;
  BinaryTree right_tree;
  left_tree._root = _root->left;
  right_tree._root = _root->right;
  if (goal == _root) { // 깊이를 구하는 노드가 루트일 경우 0
    return 0;
  }
  if (_root->left != NULL) {
    depth += left_tree.TrueDepth(goal);
  }
  if (_root->right != NULL) {
    depth += right_tree.TrueDepth(goal);
  }
  if (depth == 0) {
    return -1;
  }

  return depth;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isReverseComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node* temp;
  string tree[8] = {}; // 노드가 100개 이하
  int height = TrueHeight(_root);
  for(int i=0;i<height;i++){
    line(_root,i,&tree[i]);
  }
  for(int i=0;i<height-1;i++){
    for(int j=0;j<tree[i].length();j++){
      if(tree[i][j] == 'X'){
       return false;
      }
        
        }}
    int check =0;
  for(int i=0;i<tree[height-1].length();i++){
    if(check == 0 && tree[height-1][i] == 'X'){
      check++;
    }
    if(check != 0 && tree[height-1][i] != 'X'){
      return false;
    }
    }
        return true;
  
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return false;
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */

void BinaryTree::line(Node *node, int lvl, string* tree){
  if(lvl != 0 && node == NULL){
    return;
  }
  if(lvl == 0){
    if(node == NULL){
      tree->push_back('X');

    }
    else{
      tree->push_back(node->value);
    }   
    return;
  }
line(node->right, lvl-1, tree);
line(node->left, lvl-1, tree);  
}

int BinaryTree::TrueHeight(Node* node){
  if(node == NULL){
    return 0;
  }
  int rigght = TrueHeight(node->right);
  int lefght = TrueHeight(node->left);
  if(rigght > lefght){
    return (rigght + 1);
  }
  else {
    return (lefght + 1);
  }
}

void BinaryTree::find_node(
    Node **node, Node *root,
    char node_value) { // node_value를 value로 가지는 node를 찾는 함수
  if (root == NULL) {
    return;
  }
  if (root->value == node_value) {
    *node = root;
  }
  find_node(node, root->left, node_value);
  find_node(node, root->right, node_value);
}

string BinaryTree::pre_out() { // 전위순회
  BinaryTree subleft;
  BinaryTree subright;
  subleft._root = _root->left;
  subright._root = _root->right;

  string traversal;
  traversal = {};

  traversal += _root->value; // 루트 추가

  traversal += " ";
  if (_root->left != NULL) {
    traversal += subleft.pre_out(); // 왼쪽 트리 추가
  }
  if (_root->right != NULL) {
    traversal += subright.pre_out(); // 오른쪽 트리 추가
  }

  return traversal;
}

string BinaryTree::post_out() { // 후위순회
  BinaryTree subleft;
  BinaryTree subright;
  subleft._root = _root->left;
  subright._root = _root->right;

  string traversal;
  traversal = {};
  if (_root->left != NULL) {
    traversal += subleft.post_out(); // 왼쪽 트리 추가
  }
  if (_root->right != NULL) {
    traversal += subright.post_out(); // 오른쪽 트리 추가
  }
  traversal += _root->value; // 루트 추가
  traversal += " ";
  
  return traversal;
}
string BinaryTree::in_out() {
  BinaryTree subleft;
  BinaryTree subright;
  subleft._root = _root->left;
  subright._root = _root->right;

  string traversal;
  traversal = {};
  if (_root->left != NULL) {
    traversal += subleft.in_out(); // 왼쪽 트리 추가
  }
  traversal += _root->value; // 루트 추가
  traversal += " ";
  if (_root->right != NULL) {
    traversal += subright.in_out(); // 오른쪽 트리 추가
  }
  return traversal;
}

int BinaryTree::TrueDepth(Node *goal) {
  BinaryTree subleft;
  BinaryTree subright;
  int subdepth = 0;
  subleft._root = _root->left;
  subright._root = _root->right;
  if (_root == NULL) {
    return 0;
  }
  if (_root == goal) {
    subdepth++;
    return subdepth;
  }
  if (_root->left != NULL) {
    subdepth += subleft.TrueDepth(goal);
    if (subdepth > 0) {
      subdepth++;
    }
  }

  if (_root->right != NULL) {
    subdepth += subright.TrueDepth(goal);
    if (subdepth > 0) {
      subdepth++;
    }
  }
  return subdepth;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
