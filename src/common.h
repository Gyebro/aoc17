//
// Created by Gyebro on 2017. 12. 01..
//

#ifndef AOC17_COMMON_H
#define AOC17_COMMON_H

#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <c++/fstream>
#include <c++/sstream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;

string file_to_string(string filename);

template<typename T>
void split(const std::string &s, char delim, T result) {
    stringstream ss(s); string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim);

/**
 * Check whether string s1 and s2 are anagrams (e.g. abcd and cadb are anagrams)
 * @param s1
 * @param s2
 * @return
 */
bool anagram_pair_test(string s1, string s2);

template<typename T>
size_t max_idx(const vector<T> v) {
    auto result = std::max_element(v.begin(), v.end());
    auto index = std::distance(v.begin(), result);
    return index;
}

string trim_spaces(const string s);

template <class Clock>
void
display_precision()
{
    typedef std::chrono::duration<double, std::nano> NS;
    NS ns = typename Clock::duration(1);
    std::cout << ns.count() << " ns\n";
}

class Clock {
private:
    chrono::high_resolution_clock::time_point t_start, t_stop;
public:
    Clock();
    void start();
    void stop();
    double read_sec();
    long long int read_millisec();
    long long int read_microsec();
    long long int read_nanosec();
    void tell_sec();
    void tell_millisec();
    void tell_microsec();
    void tell_nanosec();
};

string bytes_to_hex_string(vector<uint8_t> bytes);

#endif //AOC17_COMMON_H
