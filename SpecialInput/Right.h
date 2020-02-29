//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_RIGHT_H
#define SHELL_RIGHT_H

#include "SpecialInput.h"

class Right : public SpecialInput {
private:
    static Right *instance;

    Right();

public:
    char *onClick(char *&lines, Log &log, char *content, int &length, char *path);

    static Right *getInstance();

};

#endif //SHELL_RIGHT_H
