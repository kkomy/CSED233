#include "b_tree.h"
#include <iostream>
#include <string>

using namespace std;

/*  Write your codes for other b_tree functions  */
BNode::BNode(int k) {
    M = k;
    keys = new int[M];
    child = new BNode * [M + 1];
    leaf = true;
    num = 0;
    for (int i = 0; i < M; i++) {
        keys[i] = 0;
    }
    for (int i = 0; i < M + 1; i++) {
        child[i] = NULL;
    }

}

void BTree::_postOrder(string& output, BNode* cur) {
    if (cur == NULL)
        return;
    for (int i = 0; i < M; i++) {
        _postOrder(output, cur->child[i]);
    }
    output.append("[");
    output.append(cur->print_key(M));
    output.append("]");
    output.append(" ");
}

void BTree::find(BNode* root, int key, BNode** node) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < M - 1; i++) {
        if (root->keys[i] == key) {
            *node = root;
            return;
        }
    }
    for (int i = 0; i < M; i++) {
        find(root->child[i], key, node);
    }
    return;
}
void BTree::inserting(BNode* root, int key) {
    if (root->leaf == true) {

        if (root->keys[0] > key) {
            for (int j = root->num - 1; j >= 0; j--) {
                root->keys[j + 1] = root->keys[j];
            }
            root->keys[0] = key;
        }
        
            for (int i = 0; i < root->num - 1; i++) {
                if (root->keys[i+1] > key && root->keys[i] < key) {
                    for (int j = root->num - 1; j > i; j--) {
                        root->keys[j + 1] = root->keys[j];
                    }
                    root->keys[i+1] = key;
                }
            }
        
        if (root->keys[root->num - 1] < key) {
            root->keys[root->num] = key;
        }
        root->num++;
    }
}

void BTree::location(BNode* root, BNode*& node, int key) {
    if (root->leaf == true) {
        node = root;
        return;
    }
    if (root->keys[0] > key) {
        location(root->child[0], node, key);
        return;
    }
    for (int i = 0; i < root->num; i++) {
        if (root->keys[i] > key) {
            location(root->child[i], node, key);
            return;
        }
    }
    if (root->keys[root->num - 1] < key) {
        location(root->child[root->num], node, key);
        return;
    }
}

void BTree::balance(BNode* root, int key, BNode* loc) {
    BNode* par = NULL;
    find_parent(_root, loc, key, &par);
    int median;
    if (M % 2 == 0) {
        median = (M / 2)-1;
    }
    else {
        median = M / 2;
    }

    if (loc->num == M) {
        if (par == loc) {
            BNode* parent = new BNode(M);
            parent->leaf = false;
            loc->num--;
            parent->keys[0] = loc->keys[median];

                BNode* baby = new BNode(M);
                for (int i = 0; i < median; i++) {
                    
                    parent->child[0] = baby;
                    parent->child[0]->keys[i] = loc->keys[i];
                }
                parent->child[0]->num = median;
                int k = 0;
                BNode* babi = new BNode(M);
                for (int i = median + 1; i < M; i++) {
                    parent->child[1] = babi;
                    parent->child[1]->keys[k] = loc->keys[i];
                    k++;
                }
                parent->child[1]->num = k;
                _root = parent;
                _root->num++;
                _root->leaf = false;

            if (loc->leaf == false) { // leaf가 아니면
                BNode* first = parent->child[0];
                BNode* second = parent->child[1];
                for (int i = 0; i <= median; i++) {
                    first->child[i] = loc->child[i];
                }
                first->num = median;
                int k = 0;
                for (int i = median + 1; i <= loc->num+1; i++) {
                    second->child[k] = loc->child[i];
                    k++;
                }
                second->num = k - 1;
                first->leaf = false;
                second->leaf = false;

            }

        }
        else { // root가 아니면
            BNode* first = new BNode(M);
            BNode* second = new BNode(M);
            for (int i = 0; i < median; i++) {
                first->keys[i] = loc->keys[i];
               
            }
            
            
            first->num = median;
            int k = 0;
            for (int i = median + 1; i < M; i++) {
                second->keys[k] = loc->keys[i];
                
                k++;
            }
            
            second->num = k;

            int part = 0; // median 넣을 자리
            while (par->num > part && par->keys[part] < loc->keys[0]) {
                part++;
            }
            for (int i = par->num; i >= part; i--) {
                par->keys[i] = par->keys[i - 1];
                par->child[i + 1] = par->child[i];
            }
            par->keys[part] = loc->keys[median]; // -------- 부모노드 키값 삽입 완료
            par->child[part] = first;
            par->child[part + 1] = second; // ----- 분할된 노드 삽입 완료
            par->num++;
            par->leaf = false;
            if (par->num == M) {
                balance(_root, par->keys[part], par);
            }

            if (loc->leaf == false) { // leaf가 아니면
                
                for (int i = 0; i <= median; i++) {
                    first->child[i] = loc->child[i];
                }
                first->child[median] = loc->child[median];
                first->num = median;
                int k = 0;
                for (int i = median + 1; i < M; i++) {
                    second->child[k] = loc->child[i];
                    k++;
                }
                second->child[k] = loc->child[M];
                second->num = k;
                first->leaf = false;
                second->leaf = false;

            }
        }
    }
}

void BTree::find_parent(BNode* root, BNode* node, int key, BNode** parent) { // 삭제노드의 부모노드 찾기
    if (node == _root) {
        *parent = node;
        return;
    }
    BNode* chan = NULL;
    if (root == NULL) {
        return;
    }
    for (int i = 0; i <= root->num; i++) {
        if (root->child[i] == node) {
            *parent = root;
            return;
        }
    }
        if (root->keys[0] > key) {
            find_parent(root->child[0], node, key, parent);
        }
        for(int i=0;i<root->num-1;i++){
            if (root->keys[i] < key && root->keys[i+1] > key) {
                find_parent(root->child[i+1], node, key, parent);
            }
        }
        if (root->keys[root->num -1] < key) {
            find_parent(root->child[root->num], node, key, parent);
        }
    return;
}

void BTree::deleting(BNode* node, int key) {
    int p = 0;
    while (node->keys[p] != key) {
        p++;
    }
    if (node->leaf == true) { // 리프노드일 때

        if (node->num > 1) { 
            for (int i = p; i < node->num - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            node->keys[node->num - 1] = 0;
            node->num--;
            return;
        }
        else { // key가 1개뿐일때
            if (node == _root) {
                _root = NULL;
                return;
            }
            BNode* parent = NULL;
            find_parent(_root, node, node->keys[0], &parent);
            BNode* left = left_sibling(node);
            BNode* right = right_sibling(node);
            if (left != NULL && left->num > 1) { // 왼쪽에서 가져오기
                int temp1, temp2;
                temp1 = left->keys[left->num - 1];
                left->keys[left->num - 1] = 0;
                left->num--;
                int k = 0;
                while (parent->child[k] != left) { // 중앙key
                    k++;
                }
                temp2 = parent->keys[k];
                parent->keys[k] = temp1;
                node->keys[0] = temp2;
            }
            else if(right != NULL && right->num > 1) {
                int temp1, temp2;
                temp1 = right->keys[0];
                for (int i = 0; i < right->num - 1; i++) {
                    right->keys[i] = right->keys[i + 1];
                }
                right->keys[right->num - 1] = 0;
                right->num--;
                int k = parent->num - 1;
                while (parent->child[k] == right) { // 중앙key
                    k--;
                }
                temp2 = parent->keys[k];
                parent->keys[k] = temp1;
                node->keys[0] = temp2;
            }
            else {
                int k = 0;
                while (parent->child[k] != left) { // 중앙key
                    k++;
                }
                if (parent->num == 1) {
                    node->keys[0] = parent->keys[0];
                    deleting(parent, parent->keys[0]);
                    return;
                }
                int temp = parent->keys[k];
                for (int i = k; i < parent->num; i++) {
                    parent->keys[i] = parent->keys[i + 1];
                    parent->child[i+1] = parent->child[i+2];
                }
                parent->keys[parent->num - 1] = 0;
                parent->child[parent->num] = NULL;
                parent->num--;
                BNode* tmp = new BNode(M);
                if(parent->child[k] != NULL)
                tmp->keys[0] = parent->child[k]->keys[0];
                tmp->keys[1] = temp;
                parent->child[k] = tmp;
                parent->child[k]->num = 2;

            }
            return;
        }
    }
    else { // 내부노드일때
        int k = 0;
        while (node->keys[k] != key) {
            k++;
        }

        BNode* left_child = node->child[k];
        BNode* right_child = node->child[k + 1];
        if (node->num > 1) { // 노드가 여러 개일때
            if (left_child != NULL) {
                BNode* change = NULL;
                find_max(left_child, &change);
                if (change->num > 1) {
                    node->keys[k] = change->keys[change->num - 1];
                    change->keys[change->num - 1] = 0;
                    change->num--;
                }
                else { // 단일노드
                    int temp = change->keys[0]; // 단일노드이므로
                    for (int i = right_child->num - 1; i >= 0; i--) {
                        right_child->keys[i+1] = right_child->keys[i];
                    }
                    right_child->keys[0] = temp;
                    for (int i = 0; i < node->num - 1; i++) {
                        node->keys[i] = node->keys[i + 1];
                        node->child[i] = node->child[i + 1];

                    }
                    node->child[node->num - 1] = node->child[node->num];
                    node->keys[node->num - 1] = 0;
                    node->child[node->num] = NULL;
                    node->num--;
                    //node->keys[0] = temp;

                    if (change->leaf == false) {
                        BNode* big = NULL;
                        find_max(left_child,&big);
                        int t = big->keys[big->num - 1];
                        deleting(big, t);
                        node->keys[k] = t;
                    }
                }
            }
            else if (right_child != NULL) {
                BNode* change = NULL;
                find_min(right_child, &change);
                if (change->num > 1) {
                    node->keys[k] = change->keys[0];
                    for (int i = 0; i < change->num - 1; i++) {
                        change->keys[i] = change->keys[i + 1];
                    }
                    change->keys[change->num - 1] = 0;
                    change->num--;
                }
                else {
                    int temp = change->keys[0];
                    deleting(change,temp);
                    node->keys[k] = temp;
                }
            }
            else { // child가 다 키가 한개일때
                
            }
        }
        else { // 노드가 1개일때
            if (node == _root) {
                if (node->child[k] != NULL && node->child[k]->num > 1) {

                   
                    if (left_child->num > 2) {
                        int temp = left_child->keys[left_child->num - 1];
                        left_child->keys[left_child->num - 1] = 0;
                        node->keys[k] = temp;
                        left_child->num--;
                    }
                    else{ // 올림 시 1개만 남으면
                        if (right_child->num > 2) { 
                            int temp = right_child->keys[0];
                            for (int i = 0; i < right_child->num - 1; i++) {
                                right_child->keys[i] = right_child->keys[i + 1];
                            }
                            right_child->keys[right_child->num - 1] = 0;
                            right_child->num--;
                            node->keys[k] = temp;
                        }
                        else {
                            int temp = left_child->keys[left_child->num - 1];
                            left_child->keys[left_child->num - 1] = 0;
                            node->keys[k] = temp;
                            left_child->num--;
                        }
                    }
                    
                }
                else if(node->child[k+1] != NULL && node->child[k+1]->num > 1) {
                    BNode* right_child = node->child[k + 1];
                    int temp = right_child->keys[0];
                    for (int i = 0; i < right_child->num - 1; i++) {
                        right_child->keys[i] = right_child->keys[i + 1];
                    }
                    right_child->keys[right_child->num - 1] = 0;
                    right_child->num--;
                    node->keys[k] = temp;
                }
                else {
                    BNode* initial = new BNode(M);

                }
            }
            else {
  


                return;
            }
        }
        return;
    }
}

BNode* BTree::left_sibling(BNode* node) {
    BNode* parent = NULL;
    find_parent(_root, node, node->keys[0], &parent);
    int i = 0;
    while (i < parent->num && node->keys[0] > parent->keys[i]) {
        i++;
    }
    if (i == 0) {
        return NULL;
    }
    else return parent->child[i - 1];
}

BNode* BTree::right_sibling(BNode* node) {
    BNode* parent = NULL;
    find_parent(_root, node, node->keys[0], &parent);
    int i = 0;
    while (i < parent->num && node->keys[0] > parent->keys[i]) {
        i++;
    }
    if (i == parent->num) {
        return NULL;
    }
    else return parent->child[i+1];
}

void BTree::find_min(BNode* root, BNode** node) {
    if (root == NULL) {
        return;
    }
    if ((*node) == NULL) {
        *node = root;
    }
    else {
        if (root->keys[0] < (*node)->keys[0]) {
            *node = root;
        }
    }
    for (int i = 0; i < root->num; i++) {
        find_min(root->child[i], node);
    }

    return;
}


void BTree::find_max(BNode* root, BNode** node) {
    if (root == NULL) {
        return;
    }
    if ((*node) == NULL) {
        *node = root;
    }
    else {
        if (root->keys[root->num - 1] > (*node)->keys[(*node)->num - 1]) {
            *node = root;
        }
    }
    for (int i = 0; i < root->num; i++) {
        find_max(root->child[i], node);
    }
    return;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string BTree::postOrder() {
    /*  Write your codes for b_tree functions  */
    string output;
    _postOrder(output, _root);
    if (output == "[] ") {
        return "-1";
    }
    if (!output.empty())
        output.pop_back();
    return output;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BTree::has_elem(int key) { //search : key값이 트리에 없으면 1 리턴
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    BNode* temp = NULL;
    find(_root, key, &temp);
    if (temp == NULL) {
        return 1;
    }
    else return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BTree::insert_elem(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    BNode* loc = NULL;
    if (_root == NULL) {
        _root = new BNode(M);
        _root->keys[0] = key;
        _root->num++;
        return 0;
    }
    location(_root, loc, key);
    inserting(loc, key);
    balance(_root, key, loc);
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BTree::delete_elem(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    BNode* loc = NULL;
    find(_root, key, &loc);
    deleting(loc, key);
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

