//
// Created by Sam on 11/11/2020.
//

#ifndef BSTBASE_TREENODE_H
#define BSTBASE_TREENODE_H

template<typename T>
class TreeNode {
public:
    TreeNode(T value) {
        this->value = value;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    };

    T getValue() {
        return value;
    };

    TreeNode<T> *getLeftChild() {
        return leftChild;
    };

    TreeNode<T> *getRightChild() {
        return rightChild;
    };

    TreeNode<T> *getParentNode() {
        return parent;
    };

    void setLeftChild(TreeNode<T> *node) {
        leftChild = node;
    };

    void setRightChild(TreeNode<T> *node) {
        rightChild = node;
    };

    void setParentNode(TreeNode<T> *node) {
        parent = node;
    };

private:
    T value;
    TreeNode<T> *leftChild;
    TreeNode<T> *rightChild;
    TreeNode<T> *parent;
};

#endif //BSTBASE_TREENODE_H
