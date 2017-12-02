#include "days.h"

int day01_a(string s) {
    int sum = 0;
    size_t len = s.size();
    for (size_t i=0; i<len-1; i++) {
        if (s[i] == s[i+1]) { sum += s[i]-'0'; }
    }
    if (s[0] == s[len-1]) { sum += s[len-1]-'0'; }
    return sum;
}

int day01_b(string s) {
    int sum = 0;
    size_t len = s.size();
    size_t step = len/2;
    for (size_t i=0; i<len-step; i++) {
        if (s[i] == s[i+step]) { sum += s[i]-'0'; }
    }
    for (size_t j=len-step; j<len; j++) {
        if (s[j] == s[j-step]) { sum += s[j]-'0'; }
    }
    return sum;
}

int day02_a(string s, char delim) {
    vector<string> lines = split(s, '\n');
    int checksum = 0;
    for (const string &line : lines) {
        vector<string> cells = split(line, delim);
        int min = stoi(cells[0]);
        int max = min;
        for (const string &c : cells) {
            int val = stoi(c);
            if(val < min) min = val;
            if(val > max) max = val;
        }
        checksum += (max-min);
    }
    return checksum;
}

int day02_b(string s, char delim) {
    vector<string> lines = split(s, '\n');
    int checksum = 0;
    for (const string &line : lines) {
        vector<string> cells = split(line, delim);
        vector<int> numbers;
        numbers.reserve(cells.size());
        for (const string &c : cells) { numbers.push_back(stoi(c)); }
        for (size_t i=1; i<numbers.size(); i++) {
            int a = numbers[i];
            for (size_t j=0; j<i; j++) {
                int b = numbers[j];
                int big = max(a,b); int small = min(a,b);
                if (big % small == 0) {
                    checksum += big/small;
                }
            }
        }
    }
    return checksum;
}

