/*
 * João Pedro Veloso, Rhodes College
 * Project #4 – Implementation of Binary Search Tree (FUN!)
 * Asks user for a text file, with words. It will list all words in the file alphabetically and list the
 * frequency in which these words appear in the text file.
 *
 */
#include <iostream>
#include "BST.h"

using namespace std;

int main() {

    BST binIgnore("ignore.txt");
    cout << "This is the in-order print of the words which will be ignored:" << endl;
    binIgnore.printAlph();
    //binIgnore.print(cout); //alternative printing function, must uncomment to use

    //ask user for filename input//
    string filename;
    cout << endl << "Which file are we reading? " << endl;
    cin >> filename;
    //Creates a binary tree that ignores words in ignore.txt, and print its content alphabetically
    //taking into account the frequency of words in said file
    BST binSearch(filename, binIgnore);
    binSearch.printAlph();

    return 0;
}

