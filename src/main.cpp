/* Define or undefine macros below for solutions */
//#define DAY01
//#define DAY02
//#define DAY03
//#define DAY04
//#define DAY05
//#define DAY06
//#define DAY07
//#define DAY08
//#define DAY09
//#define DAY10
//#define DAY11
//#define DAY12
//#define DAY13
//#define DAY14
//#define DAY15
#define DAY16

#include "macros.h"

#include "days.h"

int main() {

#ifndef RUN_BENCHMARKS

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

#ifdef DAY07
    cout << "Day 07: Part One and Two\n";
    day07_a(file_to_string("day07.txt"), true);
#endif

#ifdef DAY08
    cout << "Day 08: Part One and Two\n";
    day08_a(file_to_string("day08.txt"), true);
#endif

#ifdef DAY09
    cout << "Day 09: Part One\n";
    cout << day09_a(file_to_string("day09.txt")) << endl;
    cout << "Day 09: Part Two\n";
    cout << day09_a(file_to_string("day09.txt"), true) << endl;
#endif

#ifdef DAY10
    cout << "Day 10: Part One\n";
    //cout << day10_a("3,4,1,5", 5) << endl;
    cout << day10_a(file_to_string("day10.txt")) << endl;
    cout << "Day 10: Part Two\n";
    cout << day10_b(file_to_string("day10.txt")) << endl;
#endif

#ifdef DAY11
    cout << "Day 11: Part One\n";
    cout << day11_a(file_to_string("day11.txt")) << endl;
    cout << "Day 11: Part Two\n";
    cout << day11_a(file_to_string("day11.txt"), true) << endl;
#endif

#ifdef DAY12
    cout << "Day 12: Part One and Two\n";
    cout << day12_a(file_to_string("day12.txt"), true) << endl;
#endif

#ifdef DAY13
    cout << "Day 13: Part One and Two\n";
    cout << day13_a(file_to_string("day13.txt"), true) << endl;
#endif

#ifdef DAY14
    cout << "Day 14: Part One and Two\n";
    string day14_input = "hwlqcszp";
    cout << day14_a(day14_input, true, true) << endl;
#endif

#ifdef DAY15
    cout << "Day 15: Part One and Two\n";
    cout << day15_a(file_to_string("day15.txt"), true) << endl;
#endif

#ifdef DAY16
    cout << "Day 16: Part One\n";
    cout << day16_a(file_to_string("day16.txt")) << endl;
    cout << "Day 16: Part Two\n";
    cout << day16_a(file_to_string("day16.txt"), true) << endl;
#endif

#endif // ifndef RUN_BENCHMARKS

#ifdef RUN_BENCHMARKS
    vector<string> tasks;
    vector<double> time_ms;

    cout << "Day 01\n";
    string day01_input = file_to_string("day01.txt");
    tasks.emplace_back("Day 01 Part One");
    tasks.emplace_back("Day 01 Part Two");
    Clock c;
    cout << day01_a(day01_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day01_b(day01_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "Day 02\n";
    string day02_input = file_to_string("day02.txt");
    tasks.emplace_back("Day 02 Part One");
    tasks.emplace_back("Day 02 Part Two");
    c.start();
    cout << day02_a(day02_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day02_b(day02_input) << endl;;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "Day 03\n";
    long int day03_input = 368078;
    tasks.emplace_back("Day 03 Part One");
    tasks.emplace_back("Day 03 Part Two");
    c.start();
    cout << day03_a(day03_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day03_b(day03_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "Day 04\n";
    string day04_input = file_to_string("day04.txt");
    tasks.emplace_back("Day 04 Part One");
    tasks.emplace_back("Day 04 Part Two");
    c.start();
    cout << day04_a(day04_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day04_b(day04_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "Day 05\n";
    string day05_input = file_to_string("day05.txt");
    tasks.emplace_back("Day 05 Part One");
    tasks.emplace_back("Day 05 Part Two");
    c.start();
    cout << day05_a(day05_input, false) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day05_a(day05_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "Day 06\n";
    string day06_input = file_to_string("day06.txt");
    tasks.emplace_back("Day 06 Part One");
    tasks.emplace_back("Day 06 Part Two");
    c.start();
    cout << day06_a(day06_input, false) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day06_a(day06_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "Day 07\n";
    string day07_input = file_to_string("day07.txt");
    tasks.emplace_back("Day 07 Part One");
    tasks.emplace_back("Day 07 Part Two");
    c.start();
    day07_a(day07_input, false);
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    day07_a(day07_input, true);
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << endl << endl;
    cout << "Task           \t\tt [ms]\n";
    cout << "---------------\t\t------\n";
    for (size_t i=0; i<tasks.size(); i++) {
        cout << tasks[i] << "\t\t" << time_ms[i] << '\n';
    }
#endif
    
    return 0;
}