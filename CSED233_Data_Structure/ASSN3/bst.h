#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree : public BinaryTree {
public:
  BinarySearchTree(){};
  ~BinarySearchTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
	void find_insert(Node* root, int key, Node* chan);
	void find(Node* root, int key, Node** chan);
	void find_delete(Node* root, Node* node, int key, Node** parent);
	Node* right_smallest(Node* head);
	int dgr(Node* node);
	void degree0(Node* node, Node** parent);
	void degree1(Node* node, Node** parent);
	void degree2(Node* node, Node** parent);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};