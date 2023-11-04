/*
 * FSTreeTraversal.cpp
 * Luis Suarez & Laura Garavito
 * April 16 2023
*/
 
#include "FSTree.h"
#include "string"
#include <iostream>


using namespace std;

void treeTraversal(DirNode *root, string path);

int main(int argc, char *argv[]){
    if (argc != 2)
        cout << "Usage: ./treeTraversal Directory"; 

    FSTree tree(argv[1]);

    treeTraversal(tree.getRoot(), "");

    return 0;
}


/*
 * name:      stripNonAlphaNum

 * purpose:   print out path to all files and non empty directories in FStree
 * returns:   none
 * arguments: root of the FSTree and string that is the path needed to be
 *            printed to terminal
 * effects:   no effects except the cout to terminal
*/
void treeTraversal(DirNode *root, string path) {
    //check if its empty
    if (root->isEmpty()) {
        return;
    }
    path = path + root->getName() + "/";
    for (int i = 0; i < root->numSubDirs(); i++){
        treeTraversal(root->getSubDir(i), path);
    }
    if (root->hasFiles()){
            for (int j = 0; j < root->numFiles(); j++) {
                cout << path;
                cout << root->getFile(j) << endl;
            }
    }
    return;
}