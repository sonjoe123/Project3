//
// Created by John Rydberg on 12/3/22.
//

#ifndef FINALPROJEXAMPLES_RELEVANCYRANKING_H
#define FINALPROJEXAMPLES_RELEVANCYRANKING_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include "queryPro.h"
#include "indexHandler.h"
#include "documentParser.h"
class relevancyRanking {
public:
    //uses documentParser parser;
    documentParser parser;

    //used in quickSort vvv in order to iterate through the vector parameters
    int partition(vector<pair<int, int>> &v, int start, int end);
    //used to sort a vector's pairs by their relevancy (second value)
    void quickSort(vector<pair<int, int>> &v, int start, int end);
    //sees two pairs second value are equal
    bool cmp(pair<int, int> &x,pair<int, int> &y);
    //used to sort a map's pairs by their relevancy (mapped value) by setting the map's
    //to a vector and running quickSort
    void sort(unordered_map<int, int> &map);
    //used while making program to print the values of all pair of all maps in a vector
    void printData(vector<unordered_map<int, int>> data);
    //compares 2 unordered maps, pruning all pairs that don't have a matching key value in both
    void intersection(unordered_map<int, int> &map1, unordered_map<int, int> &map2);
    //does the opposite of void intersection ^^^
    //when comparing the two maps if the second map parameter has a key value that matches a
    //  pair in the first map parameter, it is removed      (prunes all intersections)
    void checkBL(unordered_map<int, int> &map1, unordered_map<int, int> &map2);
    //combines all mapped values of the parameters
    void combine(vector<unordered_map<int, int>> &v);
    //this takes all the words, organizations, people, and ignore words to look for and
    //  returns a map containing pairs of the desired docs(key values) and their
    //  relevancy score (mapped value)
    unordered_map<int, int>  rank(vector<string> keywords, vector<string> organizations, vector<string> people, vector<string> ignore, string folderName);
};


#endif //FINALPROJEXAMPLES_RELEVANCYRANKING_H
