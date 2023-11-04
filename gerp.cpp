/*
 * gerp.cpp
 * Luis Suarez & Laura Garavito
 * April 16 2023
 * Purpose: Interface for Gerp class, only the constructor and the running of
            the query is needed by the user. This program builds an indexing of
            all the files in given directory by the user and then asks the user
            for words they might want to find in their directory and stores
            the path and line that the word is on!
 * Known Bugs: takes up a lot of space and quite some time (Not VERY long but 
               still considerable). There is probably a way to make it faster,
               but we feel like with the know data structures this is quite
               good.
*/

#include "gerp.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <utility>
#include <stdexcept>

using namespace std;


const string INSENSITIVE = "@insensitive";
const string INS = "@i";
const string QUIT = "@quit";
const string Q = "@q";
const string F = "@f";

/*
 * name:      Gerp

 * purpose:   Intialize the Gerp
 * returns:   none
 * arguments: name of the directory [string]
 * effects:   Initializes Gerp by reading all the files in directory given
 */
Gerp::Gerp(string directoryname) {
    FSTree tree;

    //to pring the same thing as the_gerp we caught the error in FSTree
    try {
        tree = FSTree(directoryname);
    } catch(const runtime_error &e) {
        abort("Could not build index, exiting.");
    }
    treeTraversal(tree.getRoot(), "");
}


/*
 * name:      runGerp

 * purpose:   Respond to queries from user
 * returns:   none
 * arguments: Input and output stream
 * effects:   calls the functions that are needed according to query
 */
void Gerp::runGerp(istream &input, ostream &output) {
    bool keep_querying = true;
    string command, word, output_name;

    //formating inspired by MetroSim formatting
    while (keep_querying) {
        cout << "Query? ";

        //this formatting is just to match the ouput of the_gerp
        if (input.eof() and keep_querying != false) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }
        input >> command;
        if (command == INSENSITIVE or command == INS) {
            input >> word;
            runInsensitive(output, word);
        } else if (command == QUIT or command == Q) {
            keep_querying = false;
            cout << "Goodbye! Thank you and have a nice day." << endl;
        } else if (command == F) {
            //this inspired from RPN calc code
            cin >> output_name;
            ofstream new_output(output_name);
            runGerp(input, new_output);
            keep_querying = false;
        } else {
            runSensitive(output, command);
        }
    } 
}

/*
 * name:      runSensitive

 * purpose:   execute the command to find a word given by user with the exact
              spelling given by the user
 * returns:   none
 * arguments: output stream word given by user
 * effects:   none
 */
void Gerp::runSensitive(ostream &output, string word) {
    string curr_word = stripNonAlphaNum(word);
    set<string> setPrint = getWordSet(curr_word);

    //to match the_gerp still prints if word is empty
    if (setPrint.empty()) {
        output << curr_word << " Not Found. Try with @insensitive or @i."; 
        output << endl;
        //make sure not to run anything else if word is not found!!
        return;
    }

    //get needed information from stored value
    int fileInd, lineInd, fileNum, lineNum = 0;
    string caseSensitiveWord = "";
    for (const string &info : setPrint) {
        fileInd =  info.find("#") + 1;
        caseSensitiveWord = info.substr(0, fileInd - 1);
        //find the word int the string
        if (curr_word == caseSensitiveWord) {
            //we know its not repeated so we call otput_info on the info #s
            lineInd =  info.find("@") + 1;
            fileNum = stoi(info.substr(fileInd, lineInd - 1));
            lineNum = stoi(info.substr(lineInd));
            outputSensitive(fileNum, lineNum, output);
        }
    }
}

/*
 * name:      outputSensitive

 * purpose:   finds information in dynamic 2d array of Files and puts it in
              given output file
 * returns:   none
 * arguments: index of the file, index of the line
 * effects:   none
 */
void Gerp::outputSensitive(int file, int line, ostream &output) {
    string pFile = all_files[file].filepath;
    string sLine = all_files[file].lines[line - 1];
    string to_output = pFile + ":" + to_string(line) + ": " + sLine + '\n';
    output << to_output;
}

/*
 * name:      getWordSet

 * purpose:   lets a user access the set of words for a given keyword
 * returns:   the set of words wanted
 * arguments: the lowercase keyword that is used to find its corresponding 
              set of strings stored in HashTable
 * effects:   none
 */
set<string> Gerp::getWordSet(string curr_word) {
    string hash_word = "";
    int l = curr_word.length();
    for (int i = 0; i < l; i++) {
        hash_word += tolower(curr_word[i]);
    }
    return all_words.getSet(hash_word);
}

/*
 * name:      run_insensitive

 * purpose:   execute the @i command
 * returns:   none
 * arguments: output stream and word that is asked
 * effects:   Get the information needed to respond to query
 */
void Gerp::runInsensitive(ostream &output, string word) {
    //find the set using the lower case non alpha num word
    string curr_word = stripNonAlphaNum(word);
    set<string> setPrint = getWordSet(curr_word);

    if (setPrint.empty()) {
        output << curr_word << " Not Found." << endl;
        return;
    }

    int fileInd, lineInd, fileNum, lineNum = 0;
    //loop thru set, we dont need the word
    for (const string &info : setPrint) {
        fileInd =  info.find("#") + 1;
        lineInd =  info.find("@") + 1;
        fileNum = stoi(info.substr(fileInd, lineInd-1));
        lineNum = stoi(info.substr(lineInd));
        output_set.insert(make_pair(fileNum, lineNum));
        //cout << fileNum << " " << lineNum << endl;
    }
    outputInsensitive(output);
    output_set.clear();

}

/*
 * name:      output_info 

 * purpose:   Outputting all information to the file
 * returns:   none
 * arguments: output stream
 * effects:   All lines are written in the output file
 */
void Gerp::outputInsensitive(ostream &output) {
    //All words in set are outputed, getting info of file and line
    for (pair<int, int> p : output_set) {
        string pFile = all_files[p.first].filepath;
        string sLine = all_files[p.first].lines[p.second - 1];
        string out = pFile + ":" + to_string(p.second) + ": " + sLine + '\n';
        output << out;
    }
}

/*
 * name:      treeTraversal

 * purpose:   print out path to all files and non empty directories in FStree
 * returns:   none
 * arguments: root of the FSTree and string that is the path needed to be
 *            printed to terminal
 * effects:   no effects except the cout to terminal
*/
void Gerp::treeTraversal(DirNode *root, string path) {
    //check if its empty
    if (root->isEmpty()) {
        return;
    }
    //Builds path as we traverse tree recursively
    path = path + root->getName() + "/";
    for (int i = 0; i < root->numSubDirs(); i++){
        treeTraversal(root->getSubDir(i), path);
    }
    //Processes the words and creates a new file in each directory
    if (root->hasFiles()){
            for (int j = 0; j < root->numFiles(); j++) {
                File new_file;
                new_file.filepath = path + root->getFile(j);
                //all_files.push_back(new_file);
                //working
                readFile(new_file);
                all_files.push_back(new_file);
            }
    }
    return;
}

/*
 * name:      readFile

 * purpose:   read and process words in the file 
 * returns:   none
 * arguments: Address of a File struct
 * effects:   All lines are pushed into vector, then each word is processed
              and added into all_words  
 */
void Gerp::readFile(File &file) {
    ifstream infile(file.filepath);
    string current_line;
    string current_word;
    
    //count files corresponding index to put with word in HashTable
    int line_number = 1;
    while (getline(infile, current_line)) {
        //here we make sure given line_number matches the index
        file.lines.push_back(current_line);
        istringstream inputLine(current_line);
        //Sends each word in the line to the wordProcessing function
        while (inputLine >> current_word) {
            wordProcessing(stripNonAlphaNum(current_word), line_number);
        }
        line_number++;
    }
}

/*
 * name:      wordProcessing 

 * purpose:   Add to all_Words string with all information needed 
              for each word
 * returns:   none
 * arguments: Word that is read at a time, number of line
 * effects:   Word is set to lowercase, and then it is added to 
              all_words hash table with the line and file num
 */
void Gerp::wordProcessing(string current_word, int line) {
    //Checks that the input word is not empty
    if (current_word == "") {return;}
    
    string hash_word = "";
    //Transforms our word to lowercases to be the key of Node
    int l = current_word.length();
    for (int i = 0; i < l; i++) {
        hash_word += tolower(current_word[i]);
    }
    //Checks index of file based on size of vector
    int sSize;
    if (all_files.empty()) {
        sSize = 0;
    } else {
        sSize = all_files.size();
    }
    //Prepares and inserts the information of word into the hash table
    string nString = current_word + "#" + to_string(sSize) 
                    + "@" + to_string(line);
    all_words.insert(hash_word, nString);
}

/*
 * name:      stripNonAlphaNum

 * purpose:   get useful string for gerp
 * returns:   the given string without non alphanumeric characters in the
 *            beginning or end
 * arguments: input string
 * effects:   no direct effect unless an address of a string is given (our plan
 *            for the actual gerp to take up less space)
*/
string Gerp::stripNonAlphaNum(string input) {
    
    //checks if input string is empty, only runs if it is not
    if (input == "") {return "";}
    int inputLength = input.length();
    int start = 0;
    int end = inputLength;

    //While loops check where the alpha characters in string start and end
    while (!isalnum(input[start]) and start < inputLength) 
        start++;
    
    while (end > 0 and !isalnum(input[end - 1])) 
        end--;
    
    //If loops keep running for whole word, then its all nonalpha
    if (start > end) 
        return "";
    
    //Extracts and returns only the alphanum substring 
    return input.substr(start, end-start);
}

/*
 * name:      print 

 * purpose:   for testing purposes, prints data stored
 * returns:   none
 * arguments: node
 * effects:   prints in terminal all data in gerp
 */
void Gerp::print() {
    for (File &files : all_files) {
        cout << "Filepath : " << files.filepath << " has size "; 
        cout << files.lines.size() << endl;
        for (string &l : files.lines) {
            cout << "        " << l << endl;
        }
    }
}

/*
 * name:      abort

 * purpose:   stop a program if something goes wrong
 * arguments: the error message wanted to be displayed
 * returns:   none
 * effects:   the program stops and an error message is displayed on terminal
 *                        
 */
void Gerp::abort(string error_message) {
    cerr << error_message << endl;
    exit(EXIT_FAILURE);
}