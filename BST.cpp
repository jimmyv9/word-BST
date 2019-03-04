//
// Created by João Pedro Veloso on 01/11/17.
// BST.cpp file, definition of BST class functions, as well as string mutator functions
//

#include "BST.h"
//functions that transform strings, in order to compare word regardless of
//punctuation around it or uppercase letters
void lowercase(string &s);
void excludepunc(string &s);

//main constructor, used for "ignore.txt"
BST::BST(const string filename) {
    root = nullptr;
    string s;
    ifstream infile;
    infile.open(filename);

    if (!infile.is_open()) {
        cerr << "Could not open file." << endl;
    }

    //checks until the file is done
    while(infile.good()) {
        infile >> s;
        add(s); //inserts string into the BST
    }
    infile.close();
}

//secondary constructor, used for counting words not in the ignore file
BST::BST(const string filename, const BST &ignore) {
    root = nullptr;
    string s;
    ifstream infile;
    infile.open(filename);

    if (!infile.is_open()) {
        cerr << "Could not open file." << endl;
    }
    //loops through file and grabs word by word
    while(infile.good()) {
        infile >> s;
        lowercase(s); //turns s into lowercase in order to properly count and exclude items,
                      //for instance, the ignore file has "i" as a word to be ignored,
                      //so we must be able to ignore "I" as well
        excludepunc(s); // excludes punctuation marks in text file, allowing words to be counted individually
        int countignore = ignore.find(s);
        if (countignore == 0) { //if word is not in ignore file, we must add it to our tree
            add(s);
        }
    }
    infile.close();
}

//destructor with recursive definition, given the deletion of a Node, deletes all of that Node's children
BST::~BST() {
    delete root;
}

//checks if BST is empty
bool BST::empty() const {
    if (root == nullptr) {return true;}
    else {return false;}
}

//checks if item is larger or smaller, splitting the tree in two (log n) to find the desired item
//could return boolean, given that the value of node->frequency changes in add() function
int BST::find(const string &item) const {
    if (empty()) {return 0;} //if empty, item is not present
    Node* curr = root;
    int found = 0;
    while (found == 0 && curr != nullptr) {
        if (item < curr->data) {
            curr = curr->left;
        }
        else if (item > curr->data) {
            curr = curr->right;
        }
        else {found++;}
    }
    return found;
}

//function given by Nyhoff's C++ textbook, slightly modified to fit this program's purpose
void BST::add(const string &item) {
    //if the tree is empty, we need to create the root
    if (empty()) {
        Node* curr = new Node(item);
        root = curr;
        return; // breaks out of function, as we don't want to
                // continue running the function, adding the first element twice
    }

    Node* curr = root;
    Node* parent = nullptr;
    bool found = false;
    while (!found && curr != nullptr) {
        parent = curr; //sets parent one step behind curr always
                       //(note: curr will move forward)
        if (item < curr->data)
            curr = curr->left;
        else if (item > curr->data)
            curr = curr->right;
        else
            found = true;
    }
    if (!found) {
        curr = new Node(item);
        if (parent == nullptr)
            root = curr;
        else if (item < parent->data)
            parent->left = curr;
        else
            parent->right = curr;
    }
    else {
        curr->frequency++; // means item was found, and its frequency has to be added accordingly
                           // allows for simple tracking of frequency of words in a text file
    }
}

//Taken from class, with some modifications
void BST::printAlph() const {
    if (empty()){
        cout << "Tree is empty." << endl;
        return;
    }
    inOrderAux(root);
}
void BST::inOrderAux(Node *subtree) const {
    if (subtree != nullptr) {
        inOrderAux(subtree->left);
        cout << subtree->data << " " << subtree->frequency << endl << flush;
        inOrderAux(subtree->right);
    }
}

//given by Prof Sanders on assignment sheet
void BST::print(ostream &out) const {
    printAux(out, 0, root);
}

//given by Prof Sanders on assignment sheet
void BST::printAux(ostream &out, int indent, Node *subtree) const {
    if (subtree != nullptr) {
        printAux(out, indent + 8, subtree->right);
        out << setw(indent) << " " << subtree->data << " " << subtree->frequency << endl;
        printAux(out, indent + 8, subtree->left);
    }
}

//function that changes string s into all lowercase
void lowercase(string &s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
}

//function that removes punctuation from string s
void excludepunc(string &s) {
    int ogLength = s.length();
    for (int i = 0; i < ogLength; i++) {
        if (ispunct(s[i])) {
            s.erase(i, 1);
            i--;
        }
    }
}