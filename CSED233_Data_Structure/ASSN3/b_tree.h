#pragma once
#include <string>

using namespace std;

class BNode {
public:
    int *keys;
    BNode** child;
    int M;
    bool leaf;
    int num;

    BNode() {
        keys= NULL;
        child = NULL;
        M = 0;
        leaf = true;
        num = 0;
    }
    BNode(int k);

    string print_key(int M) {
        string output;
        for (int i = 0; i < M; i++) {
            if (keys[i] != 0) {
                output += to_string(keys[i]);
                    output += ",";
                    output += " ";

            }
        }
        output.pop_back();
        output.pop_back();
        return output;
    }
};

class BTree {
public:

    /////////////////////////////////////////////////////////
    //////  TODO: Implement BTree class, Add public members if required ///////////
    BNode* _root;
    int M;
    BTree() {
        _root = NULL;
        M = 0;
    }
    BTree(int m) {
        _root = NULL;
        M = m;
    }
    ~BTree() {
        delete[] _root;
        _root = NULL;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    int has_elem(int key);
    int insert_elem(int key);
    int delete_elem(int key);
    string postOrder();


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    void _postOrder(string& output, BNode* cur);
    void find(BNode* root, int key, BNode** chan);
    void inserting(BNode* root, int key);
    void location(BNode* root, BNode*& node, int key);
    void balance(BNode* root, int key, BNode* loc);
    void find_parent(BNode* root, BNode* node, int key, BNode** parent);
    void deleting(BNode* node, int key);
    BNode* left_sibling(BNode* node);
    BNode* right_sibling(BNode* node);
    void find_max(BNode* root, BNode** node);
    void find_min(BNode* root, BNode** node);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
