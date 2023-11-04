/*
 * Name: Laura Garavito and Luis Suarez
 * Date: April 30
 * Title: gerp.h
 * Purpose: Interface for Gerp class, defining variables that make the
            program run. Uses a HashTable class to store all the words in a
            given directory which is organized using FSTree class. Runs the 
            total program which lets a user find any word case sensitive or
            not in a given directory of thier choice and outputs it to file
            given by user. 
 * Known Bugs: - 
*/



#ifndef GERP_H
#define GERP_H

#include "FSTree.h"
#include "HashTable.h"
#include <cstdlib>
#include <sstream>

using namespace std;
    
class Gerp {
public:
    Gerp() {};
    Gerp(string directoryname);
    void runGerp(istream &input, ostream &output);

private:
    struct File {
        string filepath;
        vector<string> lines;
    };

    vector<File> all_files;
    HashTable all_words;
    set<pair<int,int>> output_set;

    //void wordProcessing(string current_word, int line);    
    string stripNonAlphaNum(string input);
    void treeTraversal(DirNode *root, string path);

    void wordProcessing(string current_word, int line); 
    set<string> getWordSet(string word);
    
    void readFile(File &file);
       
    void runSensitive(ostream &output, string word);
    void outputSensitive(int file, int line, ostream &output);

    void runInsensitive(ostream &output, string word);
    void outputInsensitive(ostream &output);
    
    void print();
    void abort(string error_message);
};

#endif
