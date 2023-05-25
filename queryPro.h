//
// Created by phant on 12/3/2022.
//

#ifndef MAIN_CPP_QUERYPRO_H
#define MAIN_CPP_QUERYPRO_H
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
class queryPro{
public:
    vector <string> input;
    vector <string> words;
    vector <string> organizations;
    vector <string> people;
    vector <string> ignore;
    bool cont;
    void takingInput(string);

};
#endif //MAIN_CPP_QUERYPRO_H
