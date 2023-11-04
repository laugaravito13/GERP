/*
 * Name: Laura Garavito and Luis Suarez
 * Date: April 30
 * Title: HashTable.h
 * Purpose: Interface for HashTable class, defining getters and modifiers that
            the class needs in gerp.cpp. Takes the keyword given by user to
            insert into the Hash Table lets the user see what they key is and
            easily inserts new values!
 * Known Bugs: Works for what it is needed. Depending on size of data being
               read. Initial table size and load factor can be modified to save
               time reading the full directory. User can test and see what is
               best but we recommend 100000 for largeGutenberg and 100 for 
               tinyData. 
*/

#include "HashTable.h"

using namespace std;

//Size can change depending on the directory we are dealing with
const int initial_size = 100000;

/*
 * name:      HashTable

 * purpose:   constructor for the hash table
 * returns:   none
 * arguments: none
 * effects:   initializes the hash table size and total number of nodes
 */
HashTable::HashTable() {
    table.resize(initial_size);
    numNodes = 0;
}

/*
 * name:      getSet

 * purpose:   lets a user (us) access the set in the desired node, takes into
              account linked nodes
 * returns:   the wanted set!
 * arguments: the keyword to find the correct set
 * effects:   user has access to the information for the keyword
 */
set<string> HashTable::getSet(string keyword) {
    //Get the index using hash function
    int index = hashing(keyword);

    //Iterates through bucket finding the right set of words
    for (Node &node : table[index]) {
        if (node.getWord() == keyword) {
            return node.getSet();
        }
    }
    //if it doesnt exist return empty set!
    return set<string> ();
}

/*
 * name:      insert

 * purpose:   inserts a word into the hashtable
 * returns:   none
 * arguments: the key word and value
 * effects:   correctly inserts value into the set for that keyword
 *            takes care of collisions or words that should go to the same 
 *            bucket
 */
void HashTable::insert(string hash_word, string info_string) {
    //Checks load factor to keep accesing time O(1)
    if (loadFactor() > 0.7) {
        expand();
    }
    int index = hashing(hash_word);

    //if the keyword is already stored just add to existing set
    for (Node &node : table[index]) {
        if (node.getWord() == hash_word) {
            //set takes care of double sensitive repeats + cuts down on storage
            node.addToSet(info_string);
            return;
        }
    }
    //only goes up if a new node has to be created if a node for that keyword
    //doesnt exist already
    numNodes++;
    table[index].push_back(Node{hash_word, info_string});
}

/*
 * name:      hashing

 * purpose:   easily finds the index a word should hash to
 * returns:   the index the word should go to int the hash table
 * arguments: the key 
 * effects:   none
 */
int HashTable::hashing(string hash_word) {
    int size = table.size();
    int key = hash_function(hash_word) % size;
    return key;
}

/*
 * name:      loadFactor

 * purpose:   easily returns a float load factor
 * returns:   the load factor of the hash table
 * arguments: none
 * effects:   none
 */
float HashTable::loadFactor() {
    return float(numNodes)/float(table.size());
}

/*
 * name:      expand

 * purpose:   called if the load factor is too big to keep finding time low
 * returns:   none
 * arguments: none
 * effects:   rehashing of all elements in hash table
 */
void HashTable::expand() {
    int size = table.size();
    //Create a new vector double the size
    vector<vector<Node>> temp(size * 2);
    for (int i = 0; i < size; i++) {
        //iterate thru buckets
        for (Node &rehash_node : table[i]) {
            // for each node (set of words) find new index and added 
            // it in the new vector
            int new_index = hash_function(rehash_node.getWord()) % (size * 2);
            temp[new_index].push_back(rehash_node);
        }
        //Empty that bucket
        table[i].clear();
    }
    //Swap elements
    table.swap(temp);
}

/*
 * name:      print

 * purpose:   prints the hash table, used for testing purposes
 * returns:   none
 * arguments: none
 * effects:   lets us see what the hash table looks like so we can see if 
 *            something is going wrong or if it looks right. also useful to 
 *            know how to iterate through the table
 */
void HashTable::print() {
    int size = table.size();
    for (int i = 0; i < size; i++) {
        cout << "At bucket " << i << endl;
        for (Node &node : table[i]) {
            //Iterate thru buckets and print each word (shows chaining)
            cout << "         Words " <<  node.getWord() << endl;
        }
    }
}

/*
 * name:      getSize 

 * purpose:   since the hash table is a private variable this lets the user
 *            know important information about the hash table size
 * returns:   the size of the hashtable
 * arguments: none
 * effects:   lets the user access the size of the hash table they created
 */
int HashTable::getSize() {
    return table.size();
}

