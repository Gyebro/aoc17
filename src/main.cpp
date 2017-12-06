/* Define or undefine macros below for solutions */
//#define DAY01
//#define DAY02
//#define DAY03
//#define DAY04
//#define DAY05
#define DAY06

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
    long int day03_input = 368078;
    cout << "Day 03: Part One\n";
    cout << day03_a(day03_input) << endl;
    cout << "Day 03: Part Two\n";
    cout << day03_b(day03_input) << endl;
#endif

#ifdef DAY04
    cout << "Day 04: Part One\n";
    cout << day04_a(file_to_string("day04.txt")) << endl;
    cout << "Day 04: Part Two\n";
    cout << day04_b(file_to_string("day04.txt")) << endl;
#endif

#ifdef DAY05
    cout << "Day 05: Part One\n";
    cout << day05_a(file_to_string("day05.txt")) << endl;
    cout << "Day 05: Part Two\n";
    cout << day05_a(file_to_string("day05.txt"), true) << endl;
#endif

#ifdef DAY06
    cout << "Day 06: Part One\n";
    cout << day06_a(file_to_string("day06.txt")) << endl;
    cout << "Day 06: Part Two\n";
    cout << day06_a(file_to_string("day06.txt"), true) << endl;
#endif
    
    return 0;
}