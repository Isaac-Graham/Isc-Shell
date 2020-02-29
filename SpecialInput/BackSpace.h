//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_BACKSPACE_H
#define SHELL_BACKSPACE_H


#include "SpecialInput.h"

class Backspace : public SpecialInput {
private:
    static Backspace *instance;

    Backspace();

public:
    char *onClick(char *&lines, Log &log, char *content, int &length, char *path);

    static Backspace *getInstance();

};

#endif //SHELL_BACKSPACE_H
