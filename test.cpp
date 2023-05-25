#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "documentParser.h"

TEST_CASE("Mapping", "[AvlTree]"){
    AvlTree<string, unordered_map<int, int>> words;
    unordered_map<int, int> myMap;
    myMap[1] = 2;
    cout << "Inserting " << "yams" << endl;
    words.insert("yams",  myMap);
    cout << "Inserting " << "potato" << endl;
    words.insert("potato",  unordered_map<int, int>());
    cout << "Inserting " << "corn" << endl;
    words.insert("corn",  unordered_map<int, int>());
    cout << "Inserting " << "pumpkin" << endl;
    words.insert("pumpkin", unordered_map<int, int>());
    cout << "Inserting " << "pear" << endl;
    words.insert("pear",  unordered_map<int, int>());
    cout << "Inserting " << "wheat" << endl;
    words.insert("wheat",  unordered_map<int, int>());
    cout << "Inserting " << "barley" << endl;
    words.insert("barley", unordered_map<int, int>());
    cout << "Inserting " << "starfruit" << endl;
    words.insert("starfruit",  unordered_map<int, int>());
    cout << "Inserting " << "lemons" << endl;
    words.insert("lemons",  unordered_map<int, int>());
    cout << "Inserting " << "coco" << endl;
    words.insert("coco",  unordered_map<int, int>());
    cout << "Inserting " << "basil" << endl;
    words.insert("basil",  unordered_map<int, int>());
    cout << "Inserting " << "pineapple" << endl;
    words.insert("pineapple",  unordered_map<int, int>());
    cout << "Inserting " << "kale" << endl;
    words.insert("kale", unordered_map<int, int>());
    cout << "Inserting " << "limes" << endl;
    words.insert("limes",  unordered_map<int, int>());
    cout << "Inserting " << "broccoli" << endl;
    words.insert("broccoli",  unordered_map<int, int>());
    cout << "Inserting " << "carrots" << endl;
    words.insert("carrots", unordered_map<int, int>());
    cout << "Inserting " << "cherries" << endl;
    words.insert("cherries", myMap);
    cout << "Inserting " << "rice" << endl;
    words.insert("rice",  myMap);

    REQUIRE(words.contains("rice")==true);
    REQUIRE(words.contains("celery")==false);
    words.prettyPrintTree();

    words.makeEmpty();
    REQUIRE(words.isEmpty()==true);
    //cout<<endl << endl << words.access("yams").element;

}

TEST_CASE("IndexHandler"){
    documentParser parse;
//    parse.tree.insertP("Carolyn", 1);
//    parse.tree.insertW("interests", 1);
//
    REQUIRE(parse.tree.organizations.isEmpty() == true);
    REQUIRE(parse.tree.people.isEmpty() == true);
    REQUIRE(parse.tree.words.isEmpty() == true);
}