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
//#define DAY16
//#define DAY17
//#define DAY18
//#define DAY19
#define DAY20

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
    cout << "Day 07: Part One\n";
    day07_a(file_to_string("day07.txt"));
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

#ifdef DAY17
    cout << "Day 17: Part One\n";
    const size_t day17_input = 376;
    cout << day17_a(day17_input) << endl;
    cout << "Day 17: Part Two\n";
    cout << day17_a(day17_input, true) << endl;
#endif

#ifdef DAY18
    cout << "Day 18: Part One\n";
    cout << day18_a(file_to_string("day18.txt")) << endl;
    cout << "Day 18: Part Two\n";
    cout << day18_a(file_to_string("day18.txt"), true) << endl;
#endif

#ifdef DAY19
    cout << "Day 19: Part One\n";
    cout << day19_a(file_to_string("day19.txt")) << endl;
    cout << "Day 19: Part Two\n";
    cout << day19_a(file_to_string("day19.txt"), true) << endl;
#endif

#ifdef DAY20
    cout << "Day 20: Part One\n";
    cout << day20_a(file_to_string("day20.txt")) << endl;
    cout << "Day 20: Part One\n";
    cout << day20_a(file_to_string("day20.txt"), true) << endl;
#endif

#endif // ifndef RUN_BENCHMARKS





#ifdef RUN_BENCHMARKS
    vector<string> tasks;
    vector<double> time_ms;

    cout << "\nDay 01\n";
    string day01_input = file_to_string("day01.txt");
    tasks.emplace_back("Day 01");
    WinClock c;
    cout << day01_a(day01_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day01_b(day01_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 02\n";
    string day02_input = file_to_string("day02.txt");
    tasks.emplace_back("Day 02");
    c.start();
    cout << day02_a(day02_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day02_b(day02_input) << endl;;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 03\n";
    long int day03_input = 368078;
    tasks.emplace_back("Day 03");
    c.start();
    cout << day03_a(day03_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day03_b(day03_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 04\n";
    string day04_input = file_to_string("day04.txt");
    tasks.emplace_back("Day 04");
    c.start();
    cout << day04_a(day04_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day04_b(day04_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 05\n";
    string day05_input = file_to_string("day05.txt");
    tasks.emplace_back("Day 05");
    c.start();
    cout << day05_a(day05_input, false) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day05_a(day05_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 06\n";
    string day06_input = file_to_string("day06.txt");
    tasks.emplace_back("Day 06");
    c.start();
    cout << day06_a(day06_input, false) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day06_a(day06_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 07\n";
    string day07_input = file_to_string("day07.txt");
    tasks.emplace_back("Day 07");
    c.start();
    day07_a(day07_input, false);
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    day07_a(day07_input, true);
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 08\n";
    string day08_input = file_to_string("day08.txt");
    tasks.emplace_back("Day 08");
    c.start();
    day08_a(day08_input, false);
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    day08_a(day08_input, true);
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 09\n";
    string day09_input = file_to_string("day09.txt");
    tasks.emplace_back("Day 09");
    c.start();
    cout << day09_a(day09_input, false) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day09_a(day09_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 10\n";
    string day10_input = file_to_string("day10.txt");
    tasks.emplace_back("Day 10");
    c.start();
    cout << day10_a(day10_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day10_b(day10_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 11\n";
    string day11_input = file_to_string("day11.txt");
    tasks.emplace_back("Day 11");
    c.start();
    cout << day11_a(day11_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day11_a(day11_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 12\n";
    string day12_input = file_to_string("day12.txt");
    tasks.emplace_back("Day 12");
    c.start();
    cout << day12_a(day12_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day12_a(day12_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 13\n";
    string day13_input = file_to_string("day13.txt");
    tasks.emplace_back("Day 13");
    c.start();
    cout << day13_a(day13_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day13_a(day13_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 14\n";
    string day14_input = "hwlqcszp";
    tasks.emplace_back("Day 14");
    c.start();
    cout << day14_a(day14_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day14_a(day14_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 15\n";
    string day15_input = file_to_string("day15.txt");
    tasks.emplace_back("Day 15");
    c.start();
    cout << day15_a(day15_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day15_a(day15_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 16\n";
    string day16_input = file_to_string("day16.txt");
    tasks.emplace_back("Day 16");
    c.start();
    cout << day16_a(day16_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day16_a(day16_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 17\n";
    const size_t day17_input = 376;
    tasks.emplace_back("Day 17");
    c.start();
    cout << day17_a(day17_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day17_a(day17_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 18\n";
    string day18_input = file_to_string("day18.txt");
    tasks.emplace_back("Day 18");
    c.start();
    cout << day18_a(day18_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day18_a(day18_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());

    cout << "\nDay 19\n";
    string day19_input = file_to_string("day19.txt");
    tasks.emplace_back("Day 19");
    c.start();
    cout << day19_a(day19_input) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());
    c.start();
    cout << day19_a(day19_input, true) << endl;
    c.stop(); time_ms.push_back(c.read_millisec());


    cout << endl << endl;
    cout << "Task  \t\tP1 [ms]\t\tP2 [ms]\n";
    cout << "------\t\t-------\t\t-------\n";
    cout << setprecision(3) << fixed;
    for (size_t i=0; i<tasks.size(); i++) {
        cout << tasks[i] << "\t\t" << time_ms[2*i] << "\t\t" << time_ms[2*i+1] << '\n';
    }
    flush(cout);

    ofstream out("README.md");
    out << "# aoc17\n";
    out << "Advent of Code 2017 in C++\n";
    out << "## Computation times\n";
    out << "Day | Part One [ms] | Part Two [ms]\n";
    out << "--- | ---: | ---:\n";
    out << setprecision(3) << fixed;
    for (size_t i=0; i<tasks.size(); i++) {
        out << tasks[i] << " | " << time_ms[2*i] << " | " << time_ms[2*i+1] << '\n';
    }
    out.close();
#endif
    
    return 0;
}