//
// Created by Gyebro on 2017. 12. 01..
//

#include <c++/algorithm>
#include "common.h"

string file_to_string(string filename) {
    std::ifstream in(filename);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

bool anagram_pair_test(string s1, string s2) {
    // Check length
    if (s1.size() == s2.size()) {
        // Sort characters and compare s1 and s2
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        return (s1 == s2);
    } else {
        // Unequal length, s1 and s2 are not anagrams
        return false;
    }
}
