//
// Created by phant on 12/3/2022.
//

#include "queryPro.h"
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include "porter2_stemmer.h"
#include <fstream>
#include <unordered_set>
#include <chrono>


using namespace std;


void queryPro::takingInput(string query) {

    //getting the query from user

    stringstream ss(query);
    string word;
    //read stop word file
    ifstream readFile("sample_data/stopWord.txt");
    unordered_set<string> stopWord;
    string myStop;
    while (!readFile.eof()) {
        getline(readFile, myStop, ' ');
        stopWord.insert(myStop);
    }
    //if the query word is not in the stop word file it will be strem then push back into a vector
    while (getline(ss, word, ' ')) {
        if (stopWord.find(word) == stopWord.end()) {
            input.push_back(word);

        }
    }
    //use the above vector then to process the query into 4 different fields
    //words, organization, person, ignore
    string temp;
    for (int i = 0; i < input.size(); i++) {
        if (input[i].substr(0, 4) == "ORG:") {
            temp = input[i].substr(4);
            replace(temp.begin(),temp.end(),'+',' ');
            organizations.push_back(temp);
        } else if (input[i].substr(0, 7) == "PERSON:") {
            temp = input[i].substr(7);
            replace(temp.begin(),temp.end(),'+',' ');
            people.push_back(temp);
        } else if (input[i].substr(0, 1) == "-") {
            Porter2Stemmer::trim(input[i]);
            Porter2Stemmer::stem(input[i]);
            ignore.push_back(input[i].substr(1));
        } else {
            Porter2Stemmer::trim(input[i]);
            Porter2Stemmer::stem(input[i]);
            words.push_back(input[i]);
        }
    }
    //if the user does not put anything or only put ignore word the program will exit
    if (input.size() == 0) {
        cont = false;
    } else if (organizations.size() == 0 && people.size() == 0 && words.size() == 0 && ignore.size() != 0) {
        cont = false;
    }
    //make all the words in all the vector lower case
    for (int i = 0; i < organizations.size(); i++) {
        for (auto &o: organizations[i]) {
            o = tolower(o);
        }
    }
    for (int i = 0; i < people.size(); i++) {
        for (auto &p: people[i]) {
            p = tolower(p);
        }
    }
    for (int i = 0; i < ignore.size(); i++) {
        for (auto &i: ignore[i]) {
            i = tolower(i);
        }
    }
    for (int i = 0; i < words.size(); i++) {
        for (auto &w: words[i]) {
            w = tolower(w);
        }
    }


    readFile.close();

}

