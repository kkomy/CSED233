#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *add = NULL;
  find_insert(_root, key, add);
  if (add == _root && add == NULL) {
    _root = new Node(key);
  }
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int BinarySearchTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *chan = NULL;
  find(_root, key, &chan);
  if (chan == NULL) {
    return -1;
  }
  Node *parent = NULL;
  find_delete(_root, chan, key, &parent);
  if (dgr(chan) == 0) {
    degree0(chan, &parent);
  } else if (dgr(chan) == 1) {
    degree1(chan, &parent);
  } else if (dgr(chan) == 2) {
    degree2(chan, &parent);
  }

  return 0;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */
void BinarySearchTree::find_insert(Node *root, int key, Node *chan) {
  if (root == NULL) {
    return;
  }
  if (root->key == key) {
    root->count++;
    return;
  }
  if (root->key > key) {
    find_insert(root->left, key, root->left);
    if (root->left == NULL) {
      root->left = new Node(key);
      chan = root->left;
    }

  } else if (root->key < key) {

    find_insert(root->right, key, root->right);
    if (root->right == NULL) {
      root->right = new Node(key);
      chan = root->right;
    }
  }
  return;
}

void BinarySearchTree::find(Node *root, int key, Node **chan) {
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

void BinarySearchTree::find_delete(Node *root, Node *node, int key,
                                   Node **parent) { // 삭제노드의 부모노드 찾기
  if (node == _root) {
    *parent = node;
    return;
  }
  if (root == NULL) {
    return;
  }
  if (root->left == node || root->right == node) {
    *parent = root;
  } else {
    if (root->key > key) {
      find_delete(root->left, node, key, parent);
    }
    if (root->key < key) {
      find_delete(root->right, node, key, parent);
    }
  }
  return;
}

Node *BinarySearchTree::right_smallest(Node *head) {
  Node *temp = head;
  while (temp->left != NULL) {
    temp = temp->left;
  }
  return temp;
}

int BinarySearchTree::dgr(Node *node) {
  if (node->left == NULL && node->right == NULL) {
    return 0;
  } else if (node->left == NULL || node->right == NULL) {
    return 1;
  } else
    return 2;
}

void BinarySearchTree::degree0(Node *node, Node **parent) {
  if (node->count > 1) {
    node->count--;
    return;
  } else {
    if ((*parent)->left == node) {
      (*parent)->left = NULL;
      return;
    } else if ((*parent)->right == node) {
      (*parent)->right = NULL;
      return;
    }
  }
}

void BinarySearchTree::degree1(Node *node, Node **parent) {
  Node *temp;
  if (node->count > 1) {
    node->count--;
    return;
  } else {
    if (node->right == NULL) {
      temp = node->left;
    } else {
      temp = node->right;
    }
    if ((*parent)->left == node) {
      (*parent)->left = temp;
      return;
    } else if ((*parent)->right == node) {
      (*parent)->right = temp;
      return;
    }
  }
}

void BinarySearchTree::degree2(Node *node, Node **parent) {
  if (node->count > 1) {
    node->count--;
    return;
  } else {
    Node *little = right_smallest(node->right);
    int dgree = dgr(little);
    Node *lit_par;
    find_delete(_root, little, little->key, &lit_par);
    node->key = little->key;
    node->count = little->count;
    node->height = little->height;
    if (dgree == 0) {
      degree0(little, &lit_par);
    } else {
      degree1(little, &lit_par);
    }
  }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
