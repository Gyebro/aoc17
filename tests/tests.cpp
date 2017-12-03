//
// Created by Gyebro on 2017. 12. 02..
//

#include <gtest/gtest.h>
#include "common.cpp"
#include "days.cpp"

TEST(Day01, PartOne) {
    EXPECT_EQ(day01_a("1122"), 3);
    EXPECT_EQ(day01_a("1111"), 4);
    EXPECT_EQ(day01_a("1234"), 0);
    EXPECT_EQ(day01_a("91212129"), 9);
}

TEST(Day01, PartTwo) {
    EXPECT_EQ(day01_b("1212"), 6);
    EXPECT_EQ(day01_b("1221"), 0);
    EXPECT_EQ(day01_b("123425"), 4);
    EXPECT_EQ(day01_b("123123"), 12);
    EXPECT_EQ(day01_b("12131415"), 4);
}

TEST(Day02, PartOne) {
    EXPECT_EQ(day02_a("5 1 9 5\n7 5 3\n2 4 6 8", ' '), 18);
}

TEST(Day02, PartTwo) {
    EXPECT_EQ(day02_b("5 9 2 8\n9 4 7 3\n3 8 6 5", ' '), 9);
}

TEST(Day03, PartOne) {
    EXPECT_EQ(3, day03_a(12));
    EXPECT_EQ(2, day03_a(23));
    EXPECT_EQ(31, day03_a(1024));
}

TEST(Day03, PartTwo) {
    EXPECT_EQ(880, day03_b(806));
}