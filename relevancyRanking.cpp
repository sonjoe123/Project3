//
// Created by John Rydberg on 12/5/22.
//

#include "relevancyRanking.h"
//used in quickSort vvv in order to iterate through the vector parameters
int relevancyRanking::partition(vector<pair<int, int>> &v, int start, int end) {
    // cout << "partitioning" << endl;
    int pivot = end;
    int j = start;
    for (int i = start; i < end; ++i) {
        if (v[i].second < v[pivot].second) {
            swap(v[i], v[j]);
            ++j;
        }
    }
    swap(v[j], v[pivot]);
    return j;

}
//used to sort a vector's pairs by their relevancy (second value)
void relevancyRanking::quickSort(vector<pair<int, int>> &v, int start, int end) {
    // cout << "accessing quicksort" << endl;
    if (start < end) {
        //cout << "start is < end" << endl;
        int p = partition(v, start, end);
        quickSort(v, start, p - 1);
        quickSort(v, p + 1, end);
    }
}
//sees two pairs second value are equal
bool relevancyRanking::cmp(pair<int, int> &x,
         pair<int, int> &y) {
    return x.second < y.second;
}
//used to sort a map's pairs by their relevancy (mapped value) by setting the map's
//to a vector and running quickSort
void relevancyRanking::sort(unordered_map<int, int> &map) {
    // Declare vector of pairs
    vector<pair<int, int> > ordered_docs;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto &x: map) {
        ordered_docs.push_back(x);
    }

    // Sort using comparator function
    quickSort(ordered_docs, 0, ordered_docs.size() - 1);

    // Print the sorted value
    map.clear();
    // cout << "Sorted Map:" << endl;
    for (auto &x: ordered_docs) {
        map[x.first] = x.second;
        // cout << x.first << " : "
        //      << x.second << endl;

    }

}
//used while making program to print the values of all pair of all maps in a vector
void relevancyRanking::printData(vector<unordered_map<int, int>> data) {
    for (auto &x: data) {
        // cout << "one map: " << endl;
        for (auto &y: x) {
            cout << y.first << " : " << y.second << endl;
        }
    }
    cout << endl;
}
//compares 2 unordered maps, pruning all pairs that don't have a matching key value in both
void relevancyRanking::intersection(unordered_map<int, int> &map1, unordered_map<int, int> &map2) {
    vector<int> toErase;
    for (auto &x: map1) {
        std::unordered_map<int, int>::const_iterator got =
                map2.find(x.first);
        if (got == map2.end()) {
            // cout << "deleting " << x.first << " from map1" << endl;
            toErase.push_back(x.first);
        }
    }
    for (auto &x: toErase) {
        map1.erase(x);
    }
    toErase.clear();
    for (auto &x: map2) {
        std::unordered_map<int, int>::const_iterator got =
                map1.find(x.first);
        if (got == map1.end()) {
            // cout << "deleting " << x.first << " from map2" << endl;
            toErase.push_back(x.first);
        }
    }
    for (auto &x: toErase) {
        map2.erase(x);
    }
}
//does the opposite of void intersection ^^^
//when comparing the two maps if the second map parameter has a key value that matches a
//  pair in the first map parameter, it is removed      (prunes all intersections)
void relevancyRanking::checkBL(unordered_map<int, int> &map1, unordered_map<int, int> &map2) {
    vector<int> toErase;
    for (auto &x: map1) {
        std::unordered_map<int, int>::const_iterator got =
                map2.find(x.first);
        if (got != map2.end()) {
            cout << "deleting " << x.first << " from map1" << endl;
            toErase.push_back(x.first);
        }
    }
    for (auto &x: toErase) {
        map1.erase(x);
    }
}
//combines all mapped values of the parameters
void relevancyRanking::combine(vector<unordered_map<int, int>> &v) {
    for (int i = 0; i < v.size() - 1; i++) {
        for (auto &x: v.at(i + 1)) {
            std::unordered_map<int, int>::const_iterator got =
                    v.at(i).find(x.first);
            x.second += got->second;
        }
    }

}
//this takes all the words, organizations, people, and ignore words to look for and
//  returns a map containing pairs of the desired docs(key values) and their
//  relevancy score (mapped value)
unordered_map<int, int> relevancyRanking::rank(vector<string> keywords, vector<string> organizations, vector<string> people, vector<string> ignore, string folderName) {



    vector<unordered_map<int, int>> poi;
    bool failed_search = false;
    for (auto &x: keywords) {
        try {
            poi.push_back(parser.tree.words.access(x)->value);
        } catch (invalid_argument& e){
            cout << "No results could be found with the search terms" << endl;
            failed_search = true;
        }
    }
    for (auto &x: organizations) {
        try {
            poi.push_back(parser.tree.organizations.access(x)->value);
        } catch (invalid_argument& e){
            cout << "No results could be found with the search terms" << endl;
            failed_search = true;
        }
    }
    for (auto &x: people) {
        try {
            poi.push_back(parser.tree.people.access(x)->value);
        } catch (invalid_argument& e){
            cout << "No results could be found with the search terms" << endl;
            failed_search = true;
        }
    }
    if (failed_search) return unordered_map<int,int>();

    if (poi.empty()){
        cout << "no search terms given" << endl;
        return unordered_map<int,int>();
    }
    for (int i = 0; i < poi.size() - 1; i++) {
        intersection(poi.at(i), poi.at(i + 1));
    }
    intersection(poi.at(poi.size() - 1), poi.at(0));

    vector<unordered_map<int, int>> blackList;
    for (auto &x: ignore) {
        blackList.push_back(parser.tree.words.access(x)->value);
    }
    if (ignore.size() > 1) {
        for (int i = 0; i < ignore.size() - 1; i++) {
            checkBL(poi.at(poi.size() - 1), blackList.at(0));
        }
    } else if (ignore.size() == 0) {
    } else if (ignore.size() == 1) {
        checkBL(poi.at(poi.size() - 1), blackList.at(0));
    }
    combine(poi);
    sort(poi.at(poi.size() - 1));


    return poi.at(poi.size() - 1);

}