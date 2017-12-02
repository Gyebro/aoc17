/* Define or undefine macros below for solutions */
//#define DAY01
//#define DAY02
#define DAY03

#include "days.h"

int main() {

#ifdef DAY01
    cout << "Day 01: Part One\n";
    cout << day01_a(file_to_string("day01.txt")) << endl;
    cout << "Day 01: Part Two\n";
    cout << day01_b(file_to_string("day01.txt")) << endl;
#endif

#ifdef DAY02
    cout << "Day 02: Part One\n";
    cout << day02_a(file_to_string("day02.txt")) << endl;
    cout << "Day 02: Part Two\n";
    cout << day02_b(file_to_string("day02.txt")) << endl;
#endif

#ifdef DAY03
    cout << "Day 03: Part One\n";
    // TODO: Tomorrow
    cout << "Day 03: Part Two\n";

#endif

    return 0;
}