//
// Created by Gyebro on 2017. 12. 01..
//

#include "common.h"

string file_to_string(string filename) {
    std::ifstream in(filename);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

