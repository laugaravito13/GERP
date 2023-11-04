###
### Makefile for gerp Project
### gerp is a program that takes a directory and allows a user to search for
### any word in the directory
###
### Author:  Laura Garavito and Luis Suarez

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -O2 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: main.o gerp.o FSTree.o DirNode.o HashTable.o Node.o
	$(CXX) $(CXXFLAGS) -o gerp $^

main.o: main.cpp gerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

HashTable.o: HashTable.cpp HashTable.h Node.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

Node.o: Node.cpp Node.h
	$(CXX) $(CXXFLAGS) -c Node.cpp

gerp.o: gerp.cpp gerp.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

stringP: stringProcessing.cpp
	$(CXX) $(CXXFLAGS) -o stringP $^

treeTraversal: FSTreeTraversal.cpp FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o treeTraversal $^

# The below rule will be used by unit_test.
unit_test: unit_test_driver.o HashTable.o Node.o gerp.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^

provide:
	provide comp15 proj4_gerp README Makefile main.cpp gerp.cpp unit_tests.h \
	HashTable.cpp HashTable.h gerp.h Node.cpp Node.h smallGin.txt tinyin.txt \
	trickySmallin.txt

provideOne:
	provide comp15 proj4_gerp_phase1 FSTreeTraversal.cpp \
	stringProcessing.h \
	stringProcessing.cpp \
	README