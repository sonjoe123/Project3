//
// Created by phant on 12/4/2022.
//
#include "userInterface.h"


using namespace std;
void userInterface::loadUserInterface() {

    cout << "Choose a folder to begin: " << endl;
    getline(cin,folderName);


    cout << "Press 1 to create index: " << endl;
    cout << "Press 2 to write persistence: " <<endl;
    cout << "Press 3 to read persistence: " <<endl;
    cout << "Press 4 to search: " << endl;
    cout << "Press 5 to see the output stat: " <<endl;
    cout << "Press 6 to clear the index: " << endl;
    cout << "Press -1 to exit: " << endl;
    string temp;
    //using cin will create an empty character after hitting the space button so have to use getline for a string then transfer that into an int
    getline(cin, temp);
    opt = stoi(temp);
    while(opt!= -1){
        if(opt == 1){
            option1();
        }
        else if (opt == 2){
            option2();
        }
        else if(opt == 3){
            option3();
        }
        else if(opt == 4){
            option4();
        }
         else if(opt == 5){
            option5();
        }
         else if(opt == 6){
             option6();
         }
        menu();
    }
}
void userInterface::menu() {
    cout << "Press 1 to create index: " << endl;
    cout << "Press 2 to write persistence: " <<endl;
    cout << "Press 3 to read persistence: " <<endl;
    cout << "Press 4 to search: " << endl;
    cout << "Press 5 to see the output stat: " <<endl;
    cout << "Press 6 to clear the index: " << endl;
    cout << "Press -1 to exit: " << endl;
    string temp;
    //using cin will create an empty character after hitting the space button so have to use getline for a string then transfer that into an int
    getline(cin, temp);
    opt = stoi(temp);
}

void userInterface::option1() {
    if(ranker.parser.tree.organizations.isEmpty() && ranker.parser.tree.words.isEmpty() && ranker.parser.tree.people.isEmpty()){
        cout << "Creating index..." << endl;
        start2 = std::chrono::high_resolution_clock::now();
        ranker.parser.readAllFiles(folderName);
        end2 = std::chrono::high_resolution_clock::now();
        time2 = end2 - start2;
    } else {
        cout << "Already have an index" << endl;
    }
}

void userInterface::option2(){
    cout << "Write persistence into output file..." << endl;
    ranker.parser.tree.writeIndex("file_organizations.txt",ranker.parser.tree.organizations,'`');
    ranker.parser.tree.writeIndex("file_people.txt",ranker.parser.tree.people,'`');
    ranker.parser.tree.writeIndex("file_words.txt",ranker.parser.tree.words,' ');
    ofstream ofs;
    ofs.open("file_articles.txt");
    for (auto &x : ranker.parser.Article){
        replace(x.title.begin(),x.title.end(),'`','\'');
        replace(x.site.begin(),x.site.end(),'`','\'');
        replace(x.date.begin(),x.date.end(),'`','\'');
        replace(x.text.begin(),x.text.end(),'`','\'');
        replace(x.text.begin(),x.text.end(),'\n',' ');
        ofs << x.title << "`" << x.site << "`" << x.date << "`" << x.docID << "`" << x.text  <<  "\n";
    }
    ofs.close();
}

void userInterface::option4() {
    vector<int> ranking;
    while(1){
        cout << "Enter Query:  ";
        string query;
        ranking.clear();
        getline(cin, query);
        if (query == "") break;
        a.takingInput(query);
        int i = 1;
        start1 = std::chrono::high_resolution_clock::now();
        for (auto &x : ranker.rank(a.words,a.organizations,a.people, a.ignore,folderName)) {
            if (i > 15) {
                break;
            }
            cout << i << ". ";
            cout << "Title: " << ranker.parser.Article[x.first].title;
            cout << " Site: " << ranker.parser.Article[x.first].site;
            cout << " Date: " << ranker.parser.Article[x.first].date;
            cout << endl;
            ranking.push_back(x.first);
            i++;
        }
        end1 = std::chrono::high_resolution_clock::now();






        time1 = end1 - start1;
        a.words.clear();
        a.ignore.clear();
        a.organizations.clear();
        a.people.clear();
        query.clear();
        a.input.clear();
        cout << endl;


        //have to set up an if statement that will only go through if there is actually document has been found otherwise continue


        cout << "Choose a file you want to look into (1-15) or hit 0 to continue searching: " << endl;
        string temp;
        int choose;
        getline(cin, temp);
        choose = stoi(temp);
        if(choose == 0){
            continue;
        } else {
            cout << ranker.parser.Article[ranking[choose-1]].text << endl;
        }

    }

}

void userInterface::option5() {
    cout << "Creating the index time: " << time2.count() << endl;
    cout << "Searching time: " << time1.count() << endl;
    cout << endl;
    cout << "Number of articles: ";
    cout <<ranker.parser.docID + 1 << endl;
}

void userInterface::option6() {
    cout << "Clearing the index..." << endl;
    ranker.parser.tree.people.makeEmpty();
    ranker.parser.tree.words.makeEmpty();
    ranker.parser.tree.organizations.makeEmpty();
}
void userInterface::option3() {
    ifstream existingFile("file_words.txt");

    if (ranker.parser.tree.words.isEmpty()) {
        if(!existingFile.is_open()) {
            ranker.parser.readAllFiles(folderName);
        }else {
            cout << "reading organizations" << endl;
            ranker.parser.tree.organizations=ranker.parser.tree.readIndex("file_organizations.txt",'`');
            cout << "reading people" << endl;
            ranker.parser.tree.people=ranker.parser.tree.readIndex("file_people.txt",'`');
            cout << "reading words" << endl;
            ranker.parser.tree.words = ranker.parser.tree.readIndex("file_words.txt",' ');
            cout << "finished reading" << endl;

            string eachLine;
            string tempString;
            article tempArticle;
            ifstream ifs;
            ifs.open("file_articles.txt");



            while(!ifs.eof()){
                getline(ifs, eachLine, '\n');
                stringstream ss(eachLine);
                getline(ss, tempArticle.title, '`');
                getline(ss, tempArticle.site, '`');
                getline(ss, tempArticle.date, '`');
                getline(ss, tempString, '`');
                tempArticle.docID = stoi(tempString);
                getline(ss, tempArticle.text, '\n');
                ranker.parser.Article.push_back(tempArticle);
            }
            ifs.close();
        }
    }
    existingFile.close();
}