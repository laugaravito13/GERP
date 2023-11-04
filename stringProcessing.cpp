/*
 * stringProcessing.cpp
 * Luis Suarez & Laura Garavito
 * April 16 2023
*/
 
#include "stringProcessing.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <string>


using namespace std;

/*
 * name:      stripNonAlphaNum

 * purpose:   get useful string for gerp
 * returns:   the given string without non alphanumeric characters in the
 *            beginning or end
 * arguments: input string
 * effects:   no direct effect unless an address of a string is given (our plan
 *            for the actual gerp to take up less space)
*/
string stripNonAlphaNum(string input) {
    int inputLength = input.length();
    int start = 0;
    int end = inputLength;
    //cout << "length : " << end << endl;
    
    while (!isalnum(input[start])) {
        start++;
    }

    //cout << "length : " << end << endl;

    while(!isalnum(input[end - 1])) {
        //cout << end << input[end - 1] << endl;
        end--;
    }
    
    //cout << "start: " << start << " end: " << end << endl;
    return input.substr(start, end-start);
}

// Test This code before using it:
// int main() {
//     //parser testP;
//     string test = "@#|@#@|#@|@#|@##@COMP15@#$%&";
//     cout << stripNonAlphaNum(test) << endl;
//     return 0;
// }