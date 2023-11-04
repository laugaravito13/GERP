/*
 * Name: Luis Suarez & Laura Garavito
 * Date: April 23 2023
 * Title: main.cpp
 * Purpose: Runs the gerp program, takes in needed data from terminal and
            only runs if the command in terminal matches the needed arguments
            to run. As a whole this program lets a user find any word with or
            without the given spelling in a given directory!
*/

#include "gerp.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

void abort(string error_message);


/* name:       main.cpp
 * Purpose:    take directory and output file from terminal, use it to run the
               Gerp Class
 * Parameters: Number of arguments and pointer to array with arguments
 * Returns:    0
 * Effects:    the index of given directory is build and the gerp program runs
 */
int main(int argc, char *argv[]){
    if (argc != 3)
        abort("Usage: ./gerp inputDirectory outputFile"); 
    
    ofstream new_output(argv[2]);
    Gerp gerp(argv[1]);
    gerp.runGerp(cin, new_output);

    return 0;
}

/*
 * name:      abort

 * purpose:   stop a program if something goes wrong
 * arguments: the error message wanted to be displayed
 * returns:   none
 * effects:   the program stops and an error message is displayed on terminal
 *                        
 */
void abort(string error_message)
{
    cerr << error_message << endl;
    exit(EXIT_FAILURE);
}