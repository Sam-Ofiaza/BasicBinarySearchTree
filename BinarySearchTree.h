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
        //First check if the root is nullptr
        if(root == nullptr) {
            root = node;
        }
        //Then find direction and check if the root has an null child pointer to add to
        //If not, start recursive method with the correct direction child to find an available pointer
        else if(node->getValue() <= root->getValue()) {
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
        TreeNode<T> *node = find(value);

        if(node == root) { //Remove root case
            TreeNode<T> *replacement = node->getRightChild();
            while(replacement->getLeftChild() != nullptr) {
                replacement = replacement->getLeftChild();
            }
            remove(replacement->getValue());

            //Set replacement's pointers to neighbors
            replacement->setLeftChild(node->getLeftChild());
            replacement->setRightChild(node->getRightChild());
            replacement->setParentNode(nullptr);

            //Set replacement's neighbor pointers to replacement
            replacement->getLeftChild()->setParentNode(replacement);
            replacement->getRightChild()->setParentNode(replacement);

            root = replacement;
            return node;
        }

        TreeNode<T> *parent = node->getParentNode();
        bool leftChild;

        //First determine if node itself is a right or left child
        if(node->getValue() <= parent->getValue()) {
            leftChild = true;
        }
        else {
            leftChild = false;
        }

        if(node->getLeftChild() == nullptr && node->getRightChild() == nullptr) { //Node has no children
            if(leftChild) {
                parent->setLeftChild(nullptr);
                node->setParentNode(nullptr);
                return node;
            }
            else {
                parent->setRightChild(nullptr);
                node->setParentNode(nullptr);
                return node;
            }
        }
        else if(node->getRightChild() == nullptr && node->getLeftChild() != nullptr) { //Only node's left child exists
            if(leftChild) {
                parent->setLeftChild(node->getLeftChild());
                parent->getLeftChild()->setParentNode(parent);
                node->setParentNode(nullptr);
                return node;
            }
            else {
                parent->setRightChild(node->getLeftChild());
                parent->getRightChild()->setParentNode(parent);
                node->setParentNode(nullptr);
                return node;
            }
        }
        else if(node->getLeftChild() == nullptr && node->getRightChild() != nullptr) { //Only node's right child exists
            if(leftChild) {
                parent->setLeftChild(node->getRightChild());
                parent->getLeftChild()->setParentNode(parent);
                node->setParentNode(nullptr);
                return node;
            }
            else {
                parent->setRightChild(node->getRightChild());
                parent->getRightChild()->setParentNode(parent);
                node->setParentNode(nullptr);
                return node;
            }
        }
        else { //Node has two children
            TreeNode<T> *replacement = node->getRightChild();
            while(replacement->getLeftChild() != nullptr) {
                replacement = replacement->getLeftChild();
            }

            remove(replacement->getValue());
            replacement->setLeftChild(node->getLeftChild());
            replacement->setRightChild(node->getRightChild());
            replacement->setParentNode(parent);

            if(leftChild) {
                parent->setLeftChild(replacement);
                node->setParentNode(nullptr);
                return node;
            }
            else {
                parent->setRightChild(replacement);
                node->setParentNode(nullptr);
                return node;
            }
        }
    };

    void rebalance() {
        vector<T> list;
        traverse(list);
        clearContents();
        rebalanceRecursively(list, 0, list.size()/2, list.size()-1);

    };

    void rebalanceRecursively(vector<T> list, int start, int half, int end) {
        TreeNode<T> *node = new TreeNode<T>(list.at(half));
        addNode(node);
        if(start <= (half+start)/2 && (half+start)/2 <= half-1) {
            rebalanceRecursively(list, start, (half+start) / 2, half - 1);
        }
        if((half+1) <= ((half+1) + end)/2 && ((half+1) + end)/2 <= end) {
            rebalanceRecursively(list, half + 1, ((half+1) + end) / 2, end);
        }
    };

    void clearContents() {
        clearContentsRecursively(root);
        root = nullptr;
    };

    //clearContents helper method - modifies vector parameter to add nodes in postorder
    //used postorder to prevent memory leaks (does it work though?)
    void clearContentsRecursively(TreeNode<T> *node){
        if(node != nullptr) {
            clearContentsRecursively(node->getLeftChild());
            clearContentsRecursively(node->getRightChild());
            node->setLeftChild(nullptr);
            node->setRightChild(nullptr);
            node->setParentNode(nullptr);
        }
    };

    void printTree() {
        vector<T> list;
        traverse(list);
        cout << "\ntree: ";
        for(T x : list) {
            cout << x << " ";
        }
    };

private:
    TreeNode<T> *root;

};

#endif //BSTBASE_BINARYSEARCHTREE_H
