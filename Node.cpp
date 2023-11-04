/*
 * Name: Laura Garavito and Luis Suarez
 * Date: April 30th
 * Title: Node.cpp
 * Purpose: The best way to use this class is if the same keyword needs to have
            multiple values stored that do not repeat
 * Known Bugs: - pretty perfect for what its used for!!!
*/

#include "Node.h"

using namespace std;

/*
 * name:      Node

 * purpose:   Constructor to initialize Node object
 * returns:   none
 * arguments: Word from query and string with the word, file and line num
 * effects:   Assigns values to the private values and set
 */
Node::Node(string keyword, string infoWord){
    word = keyword;
    words.insert(infoWord);
}

/*
 * name:      getWord

 * purpose:   Gets the keyword that identifies the node
 * returns:   keyword
 * arguments: none
 * effects:   none
 */
string Node::getWord() {
    return word;
}

/*
 * name:      addToSet

 * purpose:   inserts a string with the information of each instance
              of a word in file
 * returns:   none
 * arguments: String with word, file numnber and line number
 * effects:   Adds the information to the set so instances in same line are 
              not repeated 
 */
void Node::addToSet(string info_string) {
    words.insert(info_string);
}

/*
 * name:      getSet

 * purpose:   lets a user access the set in node its called on
 * returns:   the set in the node called on
 * arguments: none
 * effects:   none 
 */
set<string> Node::getSet() {
    return words;
}
