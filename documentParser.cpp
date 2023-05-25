//
// Created by phant on 12/1/2022.
//
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
#include "documentParser.h"
#include "article.h"

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;
void documentParser::readJsonFile(const string &fileName) {
    // open an ifstream on the file of interest and check that it could be opened.
    ifstream input(fileName);
    if (!input.is_open())
    {
        cerr << "cannot open file: " << fileName << endl;
        return;
    }

    // Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);


    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    Document d;
    d.ParseStream(isw);

    // Now that the document is parsed, we can access different elements the JSON using
    // familiar subscript notation.

    // This accesses the -title- element in the JSON. Since the value
    //  associated with title is a string (rather than
    //  an array or something else), we call the GetString()
    //  function to return the actual title of the article
    //  as a c-string.
    //get the title
    string title = d["title"].GetString();
    //get the publication
    string site = d["thread"]["site_full"].GetString();
    //get the date published
    string date = d["published"].GetString();
    //get the article text
    string text = d["text"].GetString();

    //read in stop word file
    ifstream readFile("sample_data/stopWord.txt");
    unordered_set <string> stopWord;
    string myStop;
    //insert all the stop word file into a set
    while(!readFile.eof()){
        getline(readFile,myStop, ' ');
        stopWord.insert(myStop);
    }
    //make a deep copy of the text to turn from string into c_string to do tokenizing
    char *valString = new char[text.length() + 1];
    strcpy(valString, text.c_str());
    for(int i = 0; i < text.size(); i++){
        valString[i] = tolower(valString[i]);
    }
    string delim = "1234567890.,/?!;:'()@#$%^&*<>+=-_\n ";
    char *token = strtok(valString, delim.c_str());
    while(token != nullptr){
        string str(token);
        //if the word is not found in the stop word list then it will be stemmed and push into the Word AVL tree
        if(stopWord.find(str) == stopWord.end()){
            Porter2Stemmer::trim(str);
            Porter2Stemmer::stem(str);
            tree.insertW(str,docID);
            wordCounts++;
        }
        token = strtok(nullptr, delim.c_str());
    }
    delete valString;
    // The Persons entity for which you're building a specific
    //  inverted index is contained in top level -entities- element.
    //  So that's why we subscript with ["entities"]["persons"].
    //  The value associated with entities>persons is an array.
    //  So we call GetArray() to get an iterable collection of elements
    auto persons = d["entities"]["persons"].GetArray();
    auto org = d["entities"]["organizations"].GetArray();


    // We iterate over the Array returned from the line above.
    //  Each element kind of operates like a little JSON document
    //  object in that you can use the same subscript notation
    //  to access particular values.

    string name;
    for (auto &p : persons)
    {
        //push person into AVL tree
        name = p["name"].GetString();
        tree.insertP(name,docID);

    }


    string organization;
    for (auto &o : org)
    {
        //push organization into  AVL tree
        organization = o["name"].GetString();
        tree.insertO(organization, docID);

    }
    //adding all the value to the article vector for user interface purpose
    article value;
    value.text = text;
    value.title = title;
    value.docID = docID;
    value.date = date;
    value.site = site;
    Article.push_back(value);


    input.close();
    readFile.close();
}
//read all the file using the same technique reading the first chose file
void documentParser::readAllFiles(const string &path) {
    auto it = filesystem::recursive_directory_iterator(path);

    for (const auto & entry : it) {
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            //need to change the parameter in index handler

            //docID will start 0 and increment every time it reads a new file
            readJsonFile(entry.path().string());
            docID++;

        }
    }
}

