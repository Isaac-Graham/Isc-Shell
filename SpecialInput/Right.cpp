//
// Created by Isaac_Chen on 2020/2/29.
//

#include "Right.h"
#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Right *Right::instance = nullptr;

Right::Right() {

}

char *Right::onClick(char *&lines, Log &log, char *content, int &length, char *path) {
    STORE_CURSOR();
    CLEAR_OUTPUT_LINE();
    printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), content);
    RESTORE_CURSOR();

    if (lines - content == length) {
        MOVE_LEFT(4);
    } else {
        MOVE_LEFT(3);
        lines++;
    }
    return nullptr;
}

Right *Right::getInstance() {
    if (instance == nullptr) {
        instance = new Right();
    }
    return instance;
}
