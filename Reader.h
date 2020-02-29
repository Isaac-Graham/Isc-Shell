//
// Created by Isaac_Chen on 2020/2/28.
//
//#ifndef SHELL_LOG_H
//#define SHELL_LOG_H

#include "Log.h"

//#endif

#ifndef MAX_CMD
#define MAX_CMD 512
#endif


#ifndef SHELL_READER_H
#define SHELL_READER_H

//#include "Log.h"

class Reader {
    static Reader *instance;

    Reader();

public:
    static Reader *getInstance();

    char get1char();

    int getInputCommand(char *lines, Log &log, char *path);
};


#endif //SHELL_READER_H
