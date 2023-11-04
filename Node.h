/*
 * Name: Laura Garavito and Luis Suarez
 * Date: April 30
 * Title: Node.h
 * Purpose: Interface for Node class, defining getters and modifiers that the
            that will be used by the HashTable class. This class defines what
            each element in the HashTable will be. The keyword and the set of 
            string with information on where to find the word with its spelling
            in each line on its correctly indexed file.
 * Known Bugs: - only works for AlphaNumeric strings, could be updated to work
                for every character!
*/

#ifndef NODE_H
#define NODE_H
#include <set>
#include <string>

using namespace std;

class Node {
public:
    Node(string keyword, string infoWord);
    string getWord();
    void addToSet(string info_string);
    set<string> getSet();

private:
    string word;
    set<string> words;
};

#endif
