/**
 * Example code related to final project
 */
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

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;

// Function Prototypes
void testReadJsonFile(const string &fileName);
void readAllFiles(const string &path);
int docID = 0;
int main()
{

    cout << "-------------------------------------------" << endl;
    cout << "------ RapidJSON Doc Parsing Example ------" << endl;
    cout << "-------------------------------------------" << endl;
    testReadJsonFile("sample_data/coll_1/news_0064567.json");
//    readAllFiles("sample_data");



    return 0;
}

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void testReadJsonFile(const string &fileName)
{
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
        auto val = d["title"].GetString();
        cout << val << endl;

    ifstream readFile("sample_data/stopWord.txt");
    unordered_set <string> stopWord;
    string myStop;

    while(!readFile.eof()){
        getline(readFile,myStop, ' ');
        stopWord.insert(myStop);
    }
    IndexHandler tree;
    string val1 = d["text"].GetString();
    char *valString = new char[val1.length() + 1];
    strcpy(valString, val1.c_str());
    for(int i = 0; i < val1.size(); i++){
        valString[i] = tolower(valString[i]);
    }
    string delim = "1234567890.,/?!;:'()@#$%^&*<>+=-_\"\" ";
    char *token = strtok(valString, delim.c_str());
    while(token != nullptr){
        string str(token);
        if(stopWord.find(str) == stopWord.end()){
            Porter2Stemmer::stem(str);
            tree.insertW(str,docID);
        }
        token = strtok(nullptr, delim.c_str());
    }
    cout << "this is the pretty print" << endl;
    tree.words.prettyPrintTree();
    cout << endl;

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
    cout << "  Person Entities:"
         << "\n";
    string name;
    for (auto &p : persons)
    {

        name = p["name"].GetString();
        tree.insertP(name,docID);

    }
    tree.people.prettyPrintTree();

    cout << endl;
    cout << "  Organizations Entities:"
         << "\n";
    string organization;
    for (auto &o : org)
    {
        organization = o["name"].GetString();
        tree.insertO(organization, docID);

    }

    tree.organizations.prettyPrintTree();

    cout << endl;

    input.close();
    readFile.close();
}
void readAllFiles(const string &path) {
    auto it = filesystem::recursive_directory_iterator(path);

    for (const auto & entry : it) {
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            docID++;
            //need to change the parameter in index handler
            if (docID % 1== 0) {
                cout << "Files searched:  " << entry << endl;
            }
            testReadJsonFile(entry.path().string());
        }
    }

}
