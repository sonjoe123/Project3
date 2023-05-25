//
// Created by phant on 12/4/2022.
//

#ifndef MAIN_CPP_USERINTERFACE_H
#define MAIN_CPP_USERINTERFACE_H
#include "relevancyRanking.h"
#include "queryPro.h"
#include <chrono>

class userInterface{
private:
    queryPro a;
    relevancyRanking ranker;
    string folderName;
    int opt;

    std::chrono::time_point<std::chrono::high_resolution_clock> start1, end1;
    std::chrono::time_point<std::chrono::high_resolution_clock> start2, end2;

    std::chrono::duration<double> time1, time2;
public:
    void loadUserInterface();
    void menu();
    void option1();
    void option2();
    void option3();
    void option4();
    void option5();
    void option6();

};
#endif //MAIN_CPP_USERINTERFACE_H
