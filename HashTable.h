/*
 * Name: Laura Garavito and Luis Suarez
 * Date: April 30
 * Title: HashTable.h
 * Purpose: Interface for HashTable class, defining the operations to store 
            all data. This stores words using a HashFunction that later lets a
            user find the information for a word in an instant! Useful for
            users that want to store multiple strings of information for one 
            word and find it with the word!
 * Known Bugs: - 
*/


#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Node.h"
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class HashTable {
public:
    HashTable();
    void insert(string hash_word, string info_string);    
    set<string> getSet(string keyword);

private:
    vector<vector<Node>> table;
    hash<string> hash_function;
    int numNodes;

    int hashing(string hash_word);
    void expand();
    float loadFactor(); 
    int getSize();
    void print();  
};

#endif