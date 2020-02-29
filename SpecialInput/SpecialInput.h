//
// Created by Isaac_Chen on 2020/2/29.
//


#ifndef SHELL_SPECIALINPUT_H
#define SHELL_SPECIALINPUT_H

#include "../Log.h"

class SpecialInput {
public:
    virtual char *onClick(char *&lines, Log &log, char *content, int &length, char *path) = 0;
};

#endif //SHELL_SPECIALINPUT_H
