//
// Created by phant on 12/3/2022.
//
#include <string>

#ifndef MAIN_CPP_ARTICLE_H
#define MAIN_CPP_ARTICLE_H
using namespace std;
//class work as a map but can hold multiple value
class article{
public:
    string title;
    string site;
    string date;
    string text;
    int docID;

    //comparison function to compare the docID and the relevancy ranking
    bool operator==(const article& rhs){
        if(docID == rhs.docID){
            return true;
        }
    }

};
#endif //MAIN_CPP_ARTICLE_H
