//
// Created by João Pedro Veloso on 01/11/17.
// BST.h file, with definition of struct Node and class BST
//
#ifndef INC_4_VELOSO_JOAO_BST_H
#define INC_4_VELOSO_JOAO_BST_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    string data;
    int frequency;
    Node* left;
    Node* right;

    //constructor for node, takes string as its datatype
    Node(string item) {
        data = item;
        frequency = 1;
        left = nullptr;
        right = nullptr;
    }

    //destructor for node, has a recursive definition, as the deletion will trigger the deletion
    //of all children until the deletion of the leaves in the tree
    ~Node() {
        delete right;
        delete left;
    }
};

class BST {
public:
    BST(const string filename); //constructor for ignore
    BST(const string filename, const BST &ignore); //constructor for every other BST other than ignore
    ~BST();
    bool empty() const;
    int find(const string &item) const;
    void add(const string &item);
    void printAlph() const;
    void print(ostream & out) const; //can be called for graph like imaging of the tree, however
                                     //it does not look visually appealing if printing a large tree

private:
    Node* root;
    void inOrderAux(Node* subtree) const; //needs to be private in order to access *root
    void printAux(ostream & out, int indent, Node* subtree) const;
};


#endif //INC_4_VELOSO_JOAO_BST_H
