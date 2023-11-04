/*
 * unit_tests.h
 *
 * CS 15 Gerp
 * by Laura Garavito and Luis Suarez 
 *
 * Uses Matt Russell's unit_test framework.
 *
 */

#include "HashTable.h"
#include "Node.h"
#include "gerp.h"
#include <cassert>
#include <set>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

//GERP UNIT TESTS

void test_wordProcessing() { 
    //empty constructor for testing purposes
    Gerp gerp_test;
    gerp_test.wordProcessing("Joke", 17);
    set<string> test_set = gerp_test.getWordSet("joke");
    string output_test;
    for (string info : test_set) {
        output_test += info;
    }

    //Index 0 because our test constructor has an empty all_files vector
    assert(output_test == "Joke#7@17");
}

//Tests that deletes all trailing and leading nonalpha characters
void test_stripNonALphaNum() {
    Gerp gerp_test("dir", "out");
    string test = "@#|@#@|#@|@#|@##@COMP15@#$%&";
    assert("COMP15" == gerp_test.stripNonAlphaNum(test));
}

Tests that checks an empty string as an input
void test_stripNonALphaNum_empty() {
    Gerp gerp_test("dir", "out");
    string test = "";
    cout << "Empty String ";
    cout << gerp_test.stripNonAlphaNum(test) << endl;
    assert("" == gerp_test.stripNonAlphaNum(test));
}

Tests that checks a string of only nonalpha characters
void test_stripNonALphaNum_removesAll() {
    Gerp gerp_test("dir", "out");
    string test = "@#|@#@|#@|@#|@##@@#$%&";
    cout << "Removing all ";
    cout << gerp_test.stripNonAlphaNum(test) << endl;
    assert("" == gerp_test.stripNonAlphaNum(test));
}


HASH TABLE UNIT TESTS::

Constructor test
void HT_constructor_test() {
    HashTable test;
}

Inserting test
void HT_insert_test() {
    HashTable table;
    table.insert("main", "main#4@5");
    table.insert("void", "void#4@10");
}

//tested size starts at 3 with load factor 0.7
//Needs 2.1 elements to rehash
void HT_expand_test() {
    HashTable table;
    assert(table.getSize() == 3);
    table.insert("main", "main#4@5");
    table.insert("void", "void#4@5");
    table.insert("hello", "hello#4@5");
    //cout << table.loadFactor() << endl;
    assert(table.loadFactor() == 1);
    table.insert("Main", "Main#4@5");
    table.insert("maIn", "maIn#4@5");
    table.insert("maybe", "maybe#4@5");
    //cout << table.getSize() << endl;
    assert(table.getSize() == 12);
    //table.print();
}


//MORE HASH TABLE UNIT TEST
//Testing to get a set that has info of all words 
void getSet_test() {
    HashTable table;
    table.insert("hello", "Hello#49@5");
    table.insert("hello", "hEllo#4@57");
    table.insert("main", "main#4@40");

    set<string> test_set = table.getSet("hello");
    string output_test;
    for (string info : test_set) {
        output_test += info;
        output_test += " ";
    }

    assert(output_test == "Hello#49@5 hEllo#4@57 ");
}

//Testing to get a set that is empty
void getSet_test_empty() {
    HashTable table;
    table.insert("hello", "Hello#49@5");
    table.insert("hello", "hEllo#4@57");
    table.insert("main", "main#4@40");

    set<string> test_set = table.getSet("void");
    assert(test_set.empty() == true);
}

//Testing to get a set that has repeated info
void getSet_test_repeated() {
    HashTable table;
    table.insert("hello", "hello#4@7");
    table.insert("hello", "hello#4@7");
    table.insert("main", "main#4@40");

    set<string> test_set = table.getSet("hello");
    string output_test;
    for (string info : test_set) {
        output_test += info;
    }
    assert(test_set.size() == 1);
    assert(output_test == "hello#4@7");
}


//NODE UNIT TESTS
//Testing nodes are working, adding duplicates that are not stored
void test_Node() {
    Node test_node("hello", "hello#4@7");
    test_node.addToSet("Hello#22@10");
    test_node.addToSet("hello#4@7");
    string output_test;
    for (string info : test_node.getSet()) {
        output_test += info;
    }
    assert(test_node.getWord() == "hello");
    assert(test_node.getSet().size() == 2);
    //cout << "test_node" << output_test << endl;
    assert(output_test == "Hello#22@10hello#4@7");

}



