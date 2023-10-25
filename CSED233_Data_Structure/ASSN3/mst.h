#pragma once
#include <string>

using namespace std;

class MultiNode {
public:
    MultiNode() : key1(0), key2(0), height(0), left(NULL), middle(NULL), right(NULL) {}
    int key1;
    int key2;
    int height;
    MultiNode* left;
    MultiNode* middle;
    MultiNode* right;
    /* Add public members if required*/
    MultiNode(int key) :key1(0), key2(0), height(0), left(NULL), middle(NULL), right(NULL) {
        key1 = key;
    }

    string print_key() {
        /////////////////////////////////////////////////////////
        //////////  TODO: Implement From Here      //////////////
        string output;
        if (key1 != 0 && key2 == 0) {
            output = to_string(key1);
        }
        else if (key1 == 0 && key2 != 0) {
            output += to_string(key2);
        }
        else if (key1 != 0 && key2 != 0) {
            output = to_string(key1);
            output += " ";
            output += to_string(key2);
        }

        return output;
        ///////////      End of Implementation      /////////////
        ///////////////////////////////////////////////////////
    };
};

class MultiWayTree {
public:
    MultiWayTree() { _root = NULL; };
    ~MultiWayTree() {
        delete[] _root;
        _root = NULL;
    };
    string preOrder();

protected:
    MultiNode* _root;

private:
    void _preOrder(string& output, MultiNode* cur);
};

class MultiWaySearchTree : public MultiWayTree {
public:
    MultiWaySearchTree() { };
    ~MultiWaySearchTree() { };

    int insert(int key);
    int remove(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int exist(MultiNode* root, int key);
    void find(MultiNode* root, int key, MultiNode** chan);
    void min_find(MultiNode* root, MultiNode** chan);
    void max_find(MultiNode* root, MultiNode** chan);
    void inserting(MultiNode* root, int key, MultiNode* chan);
    void remake(MultiNode*& root, int key);
    void removing(MultiNode*& root, int key);
    void find_parent(MultiNode* root, MultiNode* node, int key, MultiNode** parent);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
