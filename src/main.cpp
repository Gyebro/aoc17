#include "common.h"

/* Define or undefine macros below for solutions and tests */
//#define DAY01_TESTS
#define DAY01

int day01(string s) {
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

int main() {

#ifdef DAY01_TESTS
    cout << day01("1122") << endl;
    cout << day01("1111") << endl;
    cout << day01("1234") << endl;
    cout << day01("91212129") << endl;

    cout << day01_b("1212") << endl;
    cout << day01_b("1221") << endl;
    cout << day01_b("123425") << endl;
    cout << day01_b("123123") << endl;
    cout << day01_b("12131415") << endl;
#endif

#ifdef DAY01
    cout << "Day 01: Part One\n";
    cout << day01(file_to_string("day01.txt")) << endl;
    cout << "Day 01: Part Two\n";
    cout << day01_b(file_to_string("day01.txt")) << endl;
#endif

    return 0;
}