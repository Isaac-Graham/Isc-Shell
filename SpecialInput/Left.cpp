//
// Created by Isaac_Chen on 2020/2/29.
//

#include "Left.h"
#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Left *Left::instance = nullptr;

Left::Left() {

}

char *Left::onClick(char *&lines, Log &log, char *content, int &length, char *path) {
    STORE_CURSOR();
    CLEAR_OUTPUT_LINE();
    printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), content);
    RESTORE_CURSOR();
    if (lines != content) {
        lines--;
        MOVE_LEFT(5);
    } else {
        MOVE_LEFT(4);
    }
    return nullptr;
}

Left *Left::getInstance() {
    if (instance == nullptr) {
        instance = new Left();
    }
    return instance;
}
