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
#endif

#endif //AOC17_MACROS_H
