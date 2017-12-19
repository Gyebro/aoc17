// Advent of Code 2017 - Solution for every day's puzzle

#ifndef AOC17_DAYS_H
#define AOC17_DAYS_H

#include "common.h"

int day01_a(string s);

int day01_b(string s);

int day02_a(string s, char delim = '\t');

int day02_b(string s, char delim = '\t');

long int day03_a(long int address);

long int day03_b(long int address);

size_t day04_a(string pplist);

size_t day04_b(string pplist);

size_t day05_a(string s, bool part_two = false);

size_t day06_a(string s, bool part_two = false);

void day07_a(string s, bool part_two = false, bool verbose = false);

void day08_a(string s, bool part_two = false, bool verbose = false);

size_t day09_a(string s, bool part_two = false);

size_t day10_a(string s, const size_t buffer_size = 256);

string day10_b(string s);

size_t day11_a(string s, bool part_two = false);

size_t day12_a(string s, bool part_two = false);

size_t day13_a(string s, bool part_two = false);

size_t day14_a(string s, bool part_two = false, bool generate_bitmap = false);

size_t day15_a(string s, bool part_two = false);

string day16_a(string s, bool part_two = false);

size_t day17_a(const size_t s, bool part_two = false);

long long int day18_a(string s, bool part_two = false);

string day19_a(string s, bool part_two = false);

#endif //AOC17_DAYS_H
