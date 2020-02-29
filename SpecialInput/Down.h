//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_DOWN_H
#define SHELL_DOWN_H

#include "SpecialInput.h"

class Down : public SpecialInput {
private:
    static Down *instance;

    Down();

public:
    char *onClick(char *&lines, Log &log, char *content, int &length, char *path);

    static Down *getInstance();

};


#endif //SHELL_DOWN_H
