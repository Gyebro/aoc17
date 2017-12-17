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
#include "windows.h"
#include "bitmap_image.h"

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

template<typename T>
size_t min_idx(const vector<T>& v) {
    auto result = std::min_element(v.begin(), v.end());
    auto index = std::distance(v.begin(), result);
    return index;
}

template<class T>
long long int find(const vector<T>& v, const T e) {
    return distance(v.begin(), find(v.begin(), v.end(), e));
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

class WinClock {
private:
    double PCFreq;
    LARGE_INTEGER li;
    __int64 CounterStart, CounterStop;
public:
    WinClock();
    void start();
    void stop();
    double read_millisec();
    double read_microsec();
};

string bytes_to_hex_string(vector<uint8_t> bytes);

string hex_string_to_binary(const string s);

const size_t colourPalette[] = {0x000000, 0x00FF00, 0x0000FF, 0xFF0000, 0x01FFFE, 0xFFA6FE, 0xFFDB66, 0x006401,
                             0x010067, 0x95003A, 0x007DB5, 0xFF00F6, 0xFFEEE8, 0x774D00, 0x90FB92, 0x0076FF,
                             0xD5FF00, 0xFF937E, 0x6A826C, 0xFF029D, 0xFE8900, 0x7A4782, 0x7E2DD2, 0x85A900,
                             0xFF0056, 0xA42400, 0x00AE7E, 0x683D3B, 0xBDC6FF, 0x263400, 0xBDD393, 0x00B917,
                             0x9E008E, 0x001544, 0xC28C9F, 0xFF74A3, 0x01D0FF, 0x004754, 0xE56FFE, 0x788231,
                             0x0E4CA1, 0x91D0CB, 0xBE9970, 0x968AE8, 0xBB8800, 0x43002C, 0xDEFF74, 0x00FFC6,
                             0xFFE502, 0x620E00, 0x008F9C, 0x98FF52, 0x7544B1, 0xB500FF, 0x00FF78, 0xFF6E41,
                             0x005F39, 0x6B6882, 0x5FAD4E, 0xA75740, 0xA5FFD2, 0xFFB167, 0x009BFF, 0xE85EBE};


template <class T>
class CircularBufferElement {
public:
    T value;
    size_t prev, next;
};

template <class T>
class CircularBuffer {
private:
    vector<CircularBufferElement<T>> e;
public:
    explicit CircularBuffer(const T& first, const size_t reserve = 0);
    const CircularBufferElement<T>& find(const T& value) const;
    CircularBufferElement<T>& find(const T& value);
    size_t find_idx(const T& value) const;
    const CircularBufferElement<T>& get(size_t idx) const;
    void insert_behind(const T& value, const T& new_elem, size_t skip = 0);
    size_t insert_behind_idx(size_t target, const T &new_elem, size_t skip = 0);

};


template<class T>
CircularBuffer<T>::CircularBuffer(const T &first, const size_t reserve) {
    CircularBufferElement<T> new_elem;
    new_elem.value = first;
    new_elem.prev = 0;
    new_elem.next = 0;
    e.resize(1);
    if (reserve > 0) {
        e.reserve(reserve);
    }
    e.push_back(new_elem);
}

template<class T>
const CircularBufferElement<T> &CircularBuffer<T>::find(const T &value) const {
    for (const CircularBufferElement<T>& elem : e) {
        if (elem.value == value) {
            return elem;
        }
    }
    return e[0];
}

template<class T>
CircularBufferElement<T> &CircularBuffer<T>::find(const T &value) {
    for (CircularBufferElement<T>& elem : e) {
        if (elem.value == value) {
            return elem;
        }
    }
    return e[0];
}

template<class T>
size_t CircularBuffer<T>::find_idx(const T &value) const {
    for (size_t i=0; i<e.size(); i++) {
        if (e[i].value == value) {
            return i;
        }
    }
    return 0;
}

template<class T>
const CircularBufferElement<T> &CircularBuffer<T>::get(size_t idx) const {
    return e[idx];
}

template<class T>
void CircularBuffer<T>::insert_behind(const T &value, const T &new_elem, size_t skip) {
    CircularBufferElement<T> cbe;
    cbe.value = new_elem;
    size_t target = find_idx(value);
    for (size_t i=0; i<skip; i++) {
        target = e[target].next;
    }
    size_t new_idx = e.size();
    size_t old_next = e[target].next;
    e[target].next = new_idx;
    cbe.next = old_next;
    cbe.prev = target;
    e.push_back(cbe);
}

template<class T>
size_t CircularBuffer<T>::insert_behind_idx(size_t target, const T &new_elem, size_t skip) {
    CircularBufferElement<T> cbe;
    cbe.value = new_elem;
    size_t new_idx = e.size();
    for (size_t i=0; i<skip; i++) {
        target = e[target].next;
    }
    size_t old_next = e[target].next;
    e[target].next = new_idx;
    cbe.next = old_next;
    cbe.prev = target;
    e.push_back(cbe);
    return new_idx;
}

#endif //AOC17_COMMON_H
