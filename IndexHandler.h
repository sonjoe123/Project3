//
// Created by John Rydberg on 11/14/22.
//

#ifndef FINALPROJEXAMPLES_INDEXHANDLER_H
#define FINALPROJEXAMPLES_INDEXHANDLER_H
#include <iostream>
#include <fstream>
#include "AvlTree.h"
#include "vector"
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include "article.h"
using namespace std;

class IndexHandler {
public:

    AvlTree<string, unordered_map<int, int>>words;
    AvlTree<string, unordered_map<int, int>>people;
    AvlTree<string, unordered_map<int, int>>organizations;
    void insertW(string , int );
    void insertO(string , int );
    void insertP(string , int );
    void writeIndex(string file,AvlTree<string, unordered_map<int, int>> tree, char stop);
    AvlTree<string, unordered_map<int, int>> readIndex (string file, char stop);

};
#endif //FINALPROJEXAMPLES_INDEXHANDLER_H
