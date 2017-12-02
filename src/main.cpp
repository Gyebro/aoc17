#include "common.h"

/* Define or undefine macros below for solutions and tests */
//#define DAY01_TESTS
//#define DAY01
//#define DAY02_TESTS
#define DAY02

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

int day02_a(string s, char delim = '\t') {
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

int day02_b(string s, char delim = '\t') {
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

int main() {

#ifdef DAY01_TESTS
    cout << day01_a("1122") << endl;
    cout << day01_a("1111") << endl;
    cout << day01_a("1234") << endl;
    cout << day01_a("91212129") << endl;

    cout << day01_b("1212") << endl;
    cout << day01_b("1221") << endl;
    cout << day01_b("123425") << endl;
    cout << day01_b("123123") << endl;
    cout << day01_b("12131415") << endl;
#endif

#ifdef DAY01
    cout << "Day 01: Part One\n";
    cout << day01_a(file_to_string("day01.txt")) << endl;
    cout << "Day 01: Part Two\n";
    cout << day01_b(file_to_string("day01.txt")) << endl;
#endif

#ifdef DAY02_TESTS
    cout << day02_a("5 1 9 5\n7 5 3\n2 4 6 8", ' ') << endl;
    cout << day02_b("5 9 2 8\n9 4 7 3\n3 8 6 5", ' ') << endl;
#endif

#ifdef DAY02
    cout << "Day 02: Part One\n";
    cout << day02_a(file_to_string("day02.txt")) << endl;
    cout << "Day 02: Part Two\n";
    cout << day02_b(file_to_string("day02.txt")) << endl;
#endif

    return 0;
}