#include "avl.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
int AVLTree::bf(Node *node) {
  return (height(node->left) - height(node->right));
}

int AVLTree::height(Node *node) {
  int x = 0;
  if (node != NULL) {
    if (height(node->left) > height(node->right)) {
      x = height(node->left) + 1;
    } else {
      x = height(node->right) + 1;
    }
  }
  return x;
}

int AVLTree::exist(Node *root, int key) {
  Node *temp = NULL;
  find(root, key, &temp);
  if (temp != NULL) {
    return 1;
  } else if (temp == NULL) {
    return 0;
  }
  return -1;
}

void AVLTree::find(Node *root, int key, Node **chan) {
  if (root == NULL) {
    return;
  }
  if (root->key == key) {
    *chan = root;
    return;
  }
  find(root->left, key, chan);
  find(root->right, key, chan);

  return;
}
void AVLTree::rightation(Node *&node) { // for LL
  Node *center = node->left;
  Node *sub = center->right;
  node->left = sub;
  Node *temp = new Node(node->key);
  temp->count = node->count;
  temp->left = node->left;
  temp->right = node->right;
  center->right = temp;
  node->key = center->key;
  node->count = center->count;
  node->left = center->left;
  node->right = center->right;
}

void AVLTree::leftation(Node *&node) { // for RR
  Node *center = node->right;
  Node *sub = center->left;
  node->right = sub;
  Node *temp = new Node(node->key);
  temp->count = node->count;
  temp->left = node->left;
  temp->right = node->right;
  center->left = node;
  node->key = center->key;
  node->count = center->count;
  node->left = center->left;
  node->right = center->right;
}

void AVLTree::LR(Node *&node) {
  leftation(node->left);
  rightation(node);
}

void AVLTree::RL(Node *&node) {
  rightation(node->right);
  leftation(node);
}

void AVLTree::balance(Node *&root) {
  if (bf(root) > 1) {
    if (bf(root->left) == 1) {
      rightation(root);
    } else {
      LR(root);
    }
  } else if (bf(root) < -1) {
    if (bf(root->right) == -1) {
      leftation(root);
    } else {
      RL(root);
    }
  }
}

void AVLTree::pivot(Node *root, Node *&pvt) {
  if (root == NULL) {
    return;
  }
  if (bf(root) > 1 || bf(root) < -1) {
    pvt = root;
  }
  pivot(root->left, pvt);
  pivot(root->right, pvt);

  return;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int AVLTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (exist(_root, key) == 1) {
    return -1;
  }
  BinarySearchTree::insert(key);
  Node *pvt = NULL;
  pivot(_root, pvt);
  if (pvt != NULL)
    balance(pvt);

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int AVLTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (exist(_root, key) == 0) {
    return -1;
  }
  BinarySearchTree::remove(key);
  Node *pvt = NULL;
  pivot(_root, pvt);
  if (pvt != NULL)
    balance(pvt);
  return 0;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
