//
// Created by Gyebro on 2017. 12. 07..
//

#ifndef AOC17_MACROS_H
#define AOC17_MACROS_H

// For fast compilation every day
#define TODAY_ONLY

// For running benchmarks
//#define RUN_BENCHMARKS

#ifdef RUN_BENCHMARKS
    #undef TODAY_ONLY
    #define DAY01
    #define DAY02
    #define DAY03
    #define DAY04
    #define DAY05
    #define DAY06
    #define DAY07
    #define DAY08
    #define DAY09
    #define DAY10
    #define DAY11
    #define DAY12
    #define DAY13
    #define DAY14
    #define DAY15
    #define DAY16
    #define DAY17
    #define DAY18
    #define DAY19
    #define DAY20
    #define DAY21
    #define DAY22
    #define DAY23
    #define DAY24
    #define DAY25
#endif

#endif //AOC17_MACROS_H
