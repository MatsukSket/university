#ifndef TREE_H
#define TREE_H

class Tree {
private:
    class Node {
    public:
        int key;
        char *data;
        Node *left;
        Node *right;

        Node(int key_, char *data_);
        ~Node();
    };

    Node *root;
    int size;

    // helper methods
    int height(Node *node) const;
    int getBalanceNum(Node *node) const;
    void swapNodes(Node *a, Node *b);
    Node* rotateLeft(Node *node);
    Node* rotateRight(Node *node);
    Node* balance(Node *nade);

    void printNode(Node *node) const;
    void printPreOrderRecursive(Node *node) const;
    void printPostOrderRecursive(Node *node) const;
    void printInOrderRecursive(Node *node) const;
    void clearRecursive(Node *node);
    void taskRecursive(Node *node) const;

public:
    Tree();
    ~Tree();

    // main methods
    int getSize() const;
    void insert(int key, char *data);
    Node* search(int key) const;
    void deleteEl(int key);

    void printPreOrder() const;
    void printPostOrder() const;
    void printInOrder() const;
    void printData(Node *node) const;
    void printKey(Node *node) const;
    void completeTask() const;
    void clearTree();
};

#endif