//
// Created by Sam on 11/11/2020.
//

#ifndef BSTBASE_BINARYSEARCHTREE_H
#define BSTBASE_BINARYSEARCHTREE_H

using namespace std;

#include "TreeNode.h"
#include <vector>
#include <iostream>

template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree(TreeNode<T> *root)
     : root(root) {};

    TreeNode<T> *getRoot() {
        return root;
    };

    void traverse(vector<T> &traversalList) const {
        traverseRecursively(traversalList, root);
    };

    //traverse helper method - modifies vector parameter to add <T> values
    void traverseRecursively(vector<T> &traversalList, TreeNode<T> *node) const {
        if(node != nullptr) {
            traverseRecursively(traversalList, node->getLeftChild());
            traversalList.push_back(node->getValue());
            traverseRecursively(traversalList, node->getRightChild());
        }
    };

    void addNode(TreeNode<T> *node) {
        //First check if the root has an null pointer to add to
        //If not, start recursive method with the correct direction child to find an available pointer
        if(node->getValue() <= root->getValue()) {
            if(root->getLeftChild() == nullptr) {
                root->setLeftChild(node);
                node->setParentNode(root);
            }
            else {
                addNodeRecursively(node, root->getLeftChild());
            }
        }
        else {
            if(root->getRightChild() == nullptr) {
                root->setRightChild(node);
                node->setParentNode(root);
            }
            else {
                addNodeRecursively(node, root->getRightChild());
            }
        }
    };

    //addNode helper method
    void addNodeRecursively(TreeNode<T> *nodeToAdd, TreeNode<T> *nodeToCompare) {
        //Compare values to traverse to the correct child
        //Before traversing, check if there is an null pointer
        //Make sure to set both child and parent pointers
        if(nodeToAdd->getValue() <= nodeToCompare->getValue()) {
            if(nodeToCompare->getLeftChild() == nullptr) {
                nodeToCompare->setLeftChild(nodeToAdd);
                nodeToAdd->setParentNode(nodeToCompare);
            }
            else {
                addNodeRecursively(nodeToAdd, nodeToCompare->getLeftChild());
            }
        }
        else {
            if(nodeToCompare->getRightChild() == nullptr) {
                nodeToCompare->setRightChild(nodeToAdd);
                nodeToAdd->setParentNode(nodeToCompare);
            }
            else {
                addNodeRecursively(nodeToAdd, nodeToCompare->getRightChild());
            }
        }
    };

    TreeNode<T> *find(T value) {
        if(root->getValue() == value) {
            return root;
        }
        else if(value < root->getValue()) {
            return findRecursively(value, root->getLeftChild());
        }
        else {
            return findRecursively(value, root->getRightChild());
        }
    };

    TreeNode<T> *findRecursively(T value, TreeNode<T> *node){
        if(node == nullptr) {
            return nullptr;
        }
        else if(node->getValue() == value) {
            return node;
        }
        else if(value < node->getValue()) {
            return findRecursively(value, node->getLeftChild());
        }
        else {
            return findRecursively(value, node->getRightChild());
        }
    };

    TreeNode<T> *remove(T value) {
        return nullptr;
    };

    void rebalance() {

    };

    void clearContents() {
        clearContentsRecursively(root);
    };

    //clearContents helper method - modifies vector parameter to add nodes in postorder
    void clearContentsRecursively(TreeNode<T> *node){
        if(node != nullptr) {
            clearContentsRecursively(node->getLeftChild());
            clearContentsRecursively(node->getRightChild());
            node->setLeftChild(nullptr);
            node->setRightChild(nullptr);
            node->setParentNode(nullptr);
        }
    };

private:
    TreeNode<T> *root;

};

#endif //BSTBASE_BINARYSEARCHTREE_H
