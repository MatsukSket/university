#include "Tree.h"
#include <iostream>
#include <iomanip>
#include <algorithm>    // max
#include <cstring>      // strcpy

Tree::Node::Node(int key_, char *data_) : key(key_), left(nullptr), right(nullptr) {
    data = new char[30];
    int i;
    for(i = 0; data_[i] != '\0'; i++)
        data[i] = data_[i];
    data[i] = '\0';
}

Tree::Node::~Node() {
    delete[] data;
}

Tree::Tree() : root(nullptr), size(0) {}

Tree::~Tree() {
    clearTree();
    root = nullptr;
}

int Tree::getSize() const {
    return size;
}

int Tree::height(Node *node) const {
    return node ? std::max(height(node->left), height(node->right)) + 1 : 0; 
}

int Tree::getBalanceNum(Node *node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

Tree::Node* Tree::rotateLeft(Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

Tree::Node* Tree::rotateRight(Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

Tree::Node* Tree::balance(Node* node) {
    int balance_num = getBalanceNum(node);

    if(balance_num > 1) {   // слева больше
        if (getBalanceNum(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if(balance_num < -1) {   // справа больше
        if(getBalanceNum(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Tree::insert(int key, char *data) {
    if(!root) {
        root = new Node(key, data);
        size++;
        return;
    }

    Node *curr = root;
    while(curr){
        if(key < curr->key){    
            if (!curr->left) {
                curr->left = new Node(key, data); 
                size++;
                break;
            }
            curr = curr->left;
        }
        else if(key > curr->key) {
            if (!curr->right) {
                curr->right = new Node(key, data);
                size++;
                break;
            }
            curr = curr->right;
            continue;
        }
        else {
            std::cout << "Key " << key << " already exists\n";
            return;
        }
    }
    root = balance(root);
    std::cout << "Element was added\n";
}

Tree::Node* Tree::search(int key) const {
    Node *curr = root;
    while(curr){
        if (key == curr->key)
            return curr;
        curr = (key < curr->key) ? curr->left : curr->right;
    }
    std::cout << "Key " << key << " not found\n";
    return nullptr;
}

void Tree::deleteEl(int key) {
    Node *curr = root;
    Node *parent = nullptr;
    bool isLeft = false;

    while(curr && curr->key != key) {
        parent = curr;
        if(key < curr->key) {
            curr = curr->left;
            isLeft = true;
        }
        else {
            curr = curr->right;
            isLeft = false;
        }
    }

    if(!curr) {
        std::cout << "Key " << key << " not found\n";
        return;
    }
    
    if(!curr->left && !curr->right) {       // нет детей
        if(!parent) {
            root = nullptr;
        }
        else if(isLeft) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete curr;
    }
    else if(!curr->left || !curr->right) {  // один ребенок
        Node *child = curr->left ? curr->left : curr->right;
        if(!parent) {
            root = child;
        }
        else if(isLeft) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        delete curr;
    }
    else {          // два ребенка
        Node *succ = curr->right;
        Node *succParent = curr;
        while(succ->left) {
            succParent = succ;
            succ = succ->left;
        }

        delete[] curr->data;
        curr->key = succ->key;
        curr->data = new char[30];
        strncpy(curr->data, succ->data, 29);
        curr->data[29] = '\0';

        if(succParent == curr) {
            succParent->right = succ->right;
        }
        else {
            succParent->left = succ->right;
        }
        delete succ;
    }
    size--;
    root = balance(root);
    std::cout << "Element was deleted\n";
}

void Tree::printData(Node *node) const {
    if(!node)   return;
    std::cout << "Data: " << node->data << '\n';
}

void Tree::printKey(Node *node) const {
    std::cout << "Key: " << node->key << '\n';
}

void Tree::printNode(Node *node) const {
    std::cout << std::setw(10) << std::left << node->key
              << node->data << '\n';
}

void Tree::printPreOrder() const {
    if(!root) {
        std::cout << "Tree is empty\n";
        return;
    }
    std::cout << " key       data\n";
    printPreOrderRecursive(root);
}

void Tree::printPreOrderRecursive(Node *node) const {
    if(!node)   return;
    printNode(node);
    printPreOrderRecursive(node->left);    
    printPreOrderRecursive(node->right);
}

void Tree::printPostOrder() const {
    if(!root) {
        std::cout << "Tree is empty\n";
        return;
    }
    std::cout << " key       data\n";
    printPostOrderRecursive(root);
}

void Tree::printPostOrderRecursive(Node *node) const {
    if(!node)   return;
    printPostOrderRecursive(node->left);    
    printPostOrderRecursive(node->right);
    printNode(node);
}

void Tree::printInOrder() const {
    if(!root) {
        std::cout << "Tree is empty\n";
        return;
    }
    std::cout << " key       data\n";
    printInOrderRecursive(root);
}

void Tree::printInOrderRecursive(Node *node) const {
    if(!node)   return;
    printInOrderRecursive(node->left);
    printNode(node);
    printInOrderRecursive(node->right);
}

void Tree::clearTree() {
    clearRecursive(root);
    root = nullptr;
    size = 0;
}

void Tree::clearRecursive(Node *node) {
    if(!node)   return;
    clearRecursive(node->left);
    clearRecursive(node->right);
    delete node;
}

void Tree::completeTask() const {
    if(!root) {
        std::cout << "Tree is empty\n";
        return;
    }
    std::cout << std::setw(10) << std::left << " key" 
              << std::setw(30) << std::left << " data"
              << " count" << '\n';
    taskRecursive(root);
}

void Tree::taskRecursive(Node *node) const {
    if(!node)   return;
    taskRecursive(node->left);

    int countChar = 0;
    while(node->data[countChar] != '\0') 
        countChar++;    
    std::cout << std::setw(10) << std::left << node->key
              << std::setw(30) << std::left << node->data
              << countChar << '\n';

    taskRecursive(node->right);
}