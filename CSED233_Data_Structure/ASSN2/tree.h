#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder(int node_value);
  string postOrder(int node_value);
  string inOrder(int node_value);
  int getDepth(int node_value);
  bool isReverseComplete();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  void find_node(Node **node, Node *root, char node_value);
  string pre_out();
  string in_out();
  string post_out();
  int TrueDepth(Node* goal);
  int compare_tree();
  bool isComplete(Node* root, int i, int n);
  int size();
  int checkpoint;
  void line(Node *node, int lvl, string* tree);
  int TrueHeight(Node* node);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
