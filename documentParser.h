//
// Created by phant on 12/1/2022.
//

#ifndef MAIN_CPP_DOCUMENTPARSER_H
#define MAIN_CPP_DOCUMENTPARSER_H
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "porter2_stemmer.h"
#include "IndexHandler.h"
#include "article.h"

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;
class documentParser{
private:

public:
    void readJsonFile(const string &fileName);
    void readAllFiles(const string &path);
    IndexHandler tree;
    vector<article> Article;
    int wordCounts;
    int docID = 0;

};
#endif //MAIN_CPP_DOCUMENTPARSER_H
