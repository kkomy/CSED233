#include "mst.h"
#include <iostream>
#include <string>

using namespace std;

string MultiWayTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void MultiWayTree::_preOrder(string &output, MultiNode *cur) {
  if (cur == NULL)
    return;

  output.append(cur->print_key());
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->middle);
  _preOrder(output, cur->right);
}

int MultiWaySearchTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (exist(_root, key) == 1) {
    return -1;
  }
  MultiNode *add = NULL;
  inserting(_root, key, add);
  if (add == _root && add == NULL) {
    _root = new MultiNode(key);
  }
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int MultiWaySearchTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (exist(_root, key) == 0) {
    return -1;
  }
  removing(_root, key);
  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
int MultiWaySearchTree::exist(MultiNode *root, int key) {
  MultiNode *temp = NULL;
  find(root, key, &temp);
  if (temp != NULL) {
    return 1;
  } else if (temp == NULL) {
    return 0;
  }
  return -1;
}
void MultiWaySearchTree::find(MultiNode *root, int key, MultiNode **chan) {
  if (root == NULL) {
    return;
  }
  if (root->key1 == key || root->key2 == key) {
    *chan = root;
    return;
  }
  find(root->left, key, chan);
  find(root->middle, key, chan);
  find(root->right, key, chan);

  return;
}

void MultiWaySearchTree::min_find(MultiNode *root, MultiNode **chan) {
  if (root == NULL) {
    return;
  }
  if ((*chan) == NULL) {
    *chan = root;
  } else {
    if (root->key1 != 0) {
      if ((*chan)->key1 != 0) { // key1 있으면
        if (root->key1 < (*chan)->key1) {
          *chan = root;
        }
      } else {
        if (root->key1 < (*chan)->key2) {
          *chan = root;
        }
      }
    } else {
      if ((*chan)->key1 != 0) { // key1 있으면
        if (root->key2 < (*chan)->key1) {
          *chan = root;
        }
      } else {
        if (root->key2 < (*chan)->key2) {
          *chan = root;
        }
      }
    }
  }
  min_find(root->left, chan);
  min_find(root->middle, chan);
  min_find(root->right, chan);

  return;
}

void MultiWaySearchTree::max_find(MultiNode *root, MultiNode **chan) {
  if (root == NULL) {
    return;
  }
  if ((*chan) == NULL) {
    *chan = root;
  } else {
    if (root->key2 != 0) {
      if ((*chan)->key2 != 0) { // key2 있으면
        if (root->key2 > (*chan)->key2) {
          *chan = root;
        }
      } else {
        if (root->key2 > (*chan)->key1) {
          *chan = root;
        }
      }
    } else {
      if ((*chan)->key2 != 0) { // key1 있으면
        if (root->key1 > (*chan)->key2) {
          *chan = root;
        }
      } else {
        if (root->key1 > (*chan)->key1) {
          *chan = root;
        }
      }
    }
  }
  max_find(root->left, chan);
  max_find(root->middle, chan);
  max_find(root->right, chan);

  return;
}

void MultiWaySearchTree::inserting(MultiNode *root, int key, MultiNode *chan) {
  if (root == NULL) {
    return;
  }
  if (root->key1 > key) {
    if (root->key2 == 0) {
      if (key < root->key1) {
        int temp = root->key1;
        root->key1 = key;
        root->key2 = temp;
      } else {
        root->key2 = key;
      }
    } else {
      inserting(root->left, key, root->left);
      if (root->left == NULL) {
        root->left = new MultiNode(key);
        chan = root->left;
      }
    }

  } else if (root->key1 < key && root->key2 > key) {
    if (root->key2 == 0) {
      if (key < root->key1) {
        int temp = root->key1;
        root->key1 = key;
        root->key2 = temp;
      } else {
        root->key2 = key;
      }
    } else {
      inserting(root->middle, key, root->middle);
      if (root->middle == NULL) {
        root->middle = new MultiNode(key);
        chan = root->middle;
      }
    }
  } else if (root->key2 < key) {
    if (root->key2 == 0) {
      if (key < root->key1) {
        int temp = root->key1;
        root->key1 = key;
        root->key2 = temp;
      } else {
        root->key2 = key;
      }
    } else {
      inserting(root->right, key, root->right);
      if (root->right == NULL) {
        root->right = new MultiNode(key);
        chan = root->right;
      }
    }
  }
  return;
}
void MultiWaySearchTree::remake(MultiNode *&root, int key) {
  MultiNode *change = NULL;
  MultiNode *parent = NULL;
  if (key == root->key1) {
    min_find(root->middle, &change);
    if (change == NULL) {
      max_find(root->left, &change);
    }
    if (change != NULL) {
      if (change->key1 != 0) {
        root->key1 = change->key1;
        remake(change, change->key1);
        if (change->key1 == 0 && change->key2 == 0) {
          find_parent(_root, root, key, &parent); // NULL 처리
          if (parent == root) {
            _root = NULL;
          }
          if (parent->left == change) {
            parent->left = NULL;
          } else if (parent->middle == change) {
            parent->middle = NULL;
          } else if (parent->right == change) {
            parent->right = NULL;
          }
        }
      } else { // change->key2가 바뀔떄
        root->key1 = change->key2;
        remake(change, change->key2);
        if (change->key1 == 0 && change->key2 == 0) {
          find_parent(_root, root, key, &parent); // NULL 처리
          if (parent == root) {
            _root = NULL;
          }
          if (parent->left == change) {
            parent->left = NULL;
          } else if (parent->middle == change) {
            parent->middle = NULL;
          } else if (parent->right == change) {
            parent->right = NULL;
          }
        }
      }

    } else {
      root->key1 = 0;
      if (root->key1 == 0 && root->key2 == 0) {
        find_parent(_root, root, key, &parent);
        if (parent == root) {
          _root = NULL;
          return;
        }
        if (parent->left == root) {
          parent->left = NULL;
        } else if (parent->middle == root) {
          parent->middle = NULL;
        } else if (parent->right == root) {
          parent->right = NULL;
        }
      }
    }

  } else if (key == root->key2) {
    min_find(root->right, &change);
    if (change == NULL) {
      max_find(root->middle, &change);
    }
    if (change != NULL) {
      if (change->key1 != 0) {
        root->key2 = change->key1;
        remake(change, change->key1);
        if (change->key2 == 0) {

          find_parent(_root, root, key, &parent); // NULL 처리
          if (parent == root) {
            _root = NULL;
          }
          if (parent->left == change) {
            parent->left = NULL;
          } else if (parent->middle == change) {
            parent->middle = NULL;
          } else if (parent->right == change) {
            parent->right = NULL;
          }
        }
      } else { // change->key2가 바뀔떄
        root->key2 = change->key2;
        remake(change, change->key2);

        find_parent(_root, root, key, &parent); // NULL 처리
        if (parent == root) {
          _root = NULL;
        }
        if (parent->left == change) {
          parent->left = NULL;
        } else if (parent->middle == change) {
          parent->middle = NULL;
        } else if (parent->right == change) {
          parent->right = NULL;
        }
      }

    } else {
      root->key2 = 0;
      if (root->key1 == 0 && root->key2 == 0) {
        find_parent(_root, root, key, &parent);
        if (parent == root) {
          _root = NULL;
          return;
        }
        if (parent->left == root) {
          parent->left = NULL;
        } else if (parent->middle == root) {
          parent->middle = NULL;
        } else if (parent->right == root) {
          parent->right = NULL;
        }
      }
    }
  }
}

void MultiWaySearchTree::removing(MultiNode *&root, int key) {
  MultiNode *temp = NULL;
  MultiNode *par = NULL;
  find(root, key, &temp);
  find_parent(_root, temp, key, &par);
  remake(temp, key);
  return;
}

void MultiWaySearchTree::find_parent(
    MultiNode *root, MultiNode *node, int key,
    MultiNode **parent) { // 삭제노드의 부모노드 찾기
  if (node == _root) {
    *parent = node;
    return;
  }
  MultiNode *chan = NULL;
  if (root == NULL) {
    return;
  }
  if ((root->left == node) || (root->middle == node) || (root->right == node)) {
    *parent = root;
  } else {
    if (root->key1 > key) {
      find_parent(root->left, node, key, parent);
    } else if (root->key1 < key && root->key2 > key) {
      find_parent(root->middle, node, key, parent);
    } else if (root->key2 < key) {
      find_parent(root->right, node, key, parent);
    }
  }
  return;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
