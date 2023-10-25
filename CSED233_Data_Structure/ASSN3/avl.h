#pragma once
#include "bst.h"

using namespace std;

class AVLTree : public BinarySearchTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    int insert(int key);
    int remove(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int bf(Node* node);
    int height(Node* node);
    int exist(Node* root, int key);
    void find(Node* root, int key, Node** chan);
    void rightation(Node*& node);
    void leftation(Node*& node);
    void LR(Node*& node);
    void RL(Node*& node);
    void balance(Node*& root);
    void pivot(Node* root, Node*& pvt);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};