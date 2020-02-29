//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_UP_H
#define SHELL_UP_H

#include "SpecialInput.h"

class Up : public SpecialInput {
private:
    static Up *instance;

    Up();

public:
    char *onClick(char *&lines, Log &log, char *content, int &length, char *path);

    static Up *getInstance();

};


#endif //SHELL_UP_H
