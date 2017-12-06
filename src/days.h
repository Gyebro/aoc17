// Advent of Code 2017 - Solution for every day's puzzle

#ifndef AOC17_DAYS_H
#define AOC17_DAYS_H

#include "common.h"
// For fast compilation every day
#define TODAY_ONLY

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

#endif //AOC17_DAYS_H
