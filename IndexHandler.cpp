//
// Created by John Rydberg on 12/5/22.
//

#include "IndexHandler.h"

void IndexHandler::insertW(string tempWord, int docID) {
    //checks to see if the word IS in the tree
    if (words.contains(tempWord)) {
        for (auto &x: words.access(tempWord)->value) {
            //checks to see if it is already in a document and if it is, the occurence is increased by 1
            if (x.first == docID) {
                x.second++;
                return;
            }
        }
        //if the code reaches this point, tempWord is in the tree, but not on a previously seen document
        //so, we add the docID and an occurrence of 1 (first time seen on this doc) to the tempWord's map
        words.access(tempWord)->value[docID] = 1;
        //reaches this point if there is no tempWord on the tree
    }else {
        //creates a map with only the doc it was first found in and an occurrence of 1
        unordered_map<int, int> tempData;
        tempData[docID] = 1;
        //tempWord and tempData are added
        words.insert(tempWord, tempData);
    }
}
void IndexHandler::insertO(string tempWord, int docID) {
    //checks to see if the word IS in the tree
    if (organizations.contains(tempWord)) {
        for (auto &x: organizations.access(tempWord)->value) {
            //checks to see if it is already in a document and if it is, the occurence is increased by 1
            if (x.first == docID) {
                x.second++;
                return;
            }
        }
        //if the code reaches this point, tempWord is in the tree, but not on a previously seen document
        //so, we add the docID and an occurrence of 1 (first time seen on this doc) to the tempWord's map
        organizations.access(tempWord)->value[docID] = 1;
        //reaches this point if there is no tempWord on the tree
    }else {
        //creates a map with only the doc it was first found in and an occurrence of 1
        unordered_map<int, int> tempData;
        tempData[docID] = 1;
        //tempWord and tempData are added
        organizations.insert(tempWord, tempData);
    }
}
void IndexHandler::insertP(string tempWord, int docID) {
    //checks to see if the word IS in the tree
    if (people.contains(tempWord)) {
        for (auto &x: people.access(tempWord)->value) {
            //checks to see if it is already in a document and if it is, the occurrence is increased by 1
            if (x.first == docID) {
                x.second++;
                return;
            }
        }
        //if the code reaches this point, tempWord is in the tree, but not on a previously seen document
        //so, we add the docID and an occurrence of 1 (first time seen on this doc) to the tempWord's map
        people.access(tempWord)->value[docID] = 1;
        //reaches this point if there is no tempWord on the tree
    }else {
        //creates a map with only the doc it was first found in and an occurrence of 1
        unordered_map<int, int> tempData;
        tempData[docID] = 1;
        //tempWord and tempData are added
        people.insert(tempWord, tempData);
    }
}
void IndexHandler::writeIndex(string file,AvlTree<string, unordered_map<int, int>> tree, char stop){

    ofstream outFS;
    //the created file's name is set to the string file parameter
    outFS.open(file);
    //this map will be filled with all the data of the AvlTree parameter
    unordered_map<string, unordered_map<int,int>> wordMap;
    //wordMap is filled with all of tree's data
    tree.convertToMap(wordMap);
    //for each pair on wordMap...
    for (auto & x : wordMap){
        //the .first/poi(word,org,person) is transcribed onto the file
        // and a colon is placed after it
        outFS << x.first << stop;
        //and the poi's map is iterated through, transcribing each pairs .first(docID) and
        // .second(the amount of times the word appears in that doc)
        for (auto & y : x.second){
            outFS << y.first << " " << y.second << ",";
        }
        outFS << endl;
    }
    outFS.close();
}

AvlTree<string, unordered_map<int, int>> IndexHandler::readIndex (string file,char stop){

    ifstream inFS;
    inFS.open(file);
    string eachLine;
    string tempWord;
    string tempString;
    string tempTempString;
    int tempDoc;
    int tempUsage;
    unordered_map<int, int> tempData;

    AvlTree<string, unordered_map<int, int>> tree;

    while(!inFS.eof()) {
        getline(inFS, eachLine, '\n');
        stringstream ss(eachLine);
        getline(ss, tempWord, stop);
        tempData.clear();
        while(getline(ss,tempString, ',')){
            stringstream ssss(tempString);
            getline(ssss, tempTempString, ' ' );
            tempDoc=stoi(tempTempString);
            getline(ssss, tempTempString, ',' );
            tempUsage=stoi(tempTempString);
            tempData[tempDoc] = tempUsage;
        }

        tree.insert(tempWord, tempData);
    }
    return tree;
}
