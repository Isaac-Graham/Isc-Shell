//
// Created by Isaac_Chen on 2020/2/29.
//

#include <cstdio>
#include <unistd.h>
#include "BackSpace.h"
#include "KeyboardOperation.h"
#include "Left.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Backspace *Backspace::instance = nullptr;

Backspace::Backspace() {

}

char *Backspace::onClick(char *&lines, Log &log, char *content, int &length, char *path) {
    if (length == 0 || lines == content) {
        CLEAR_OUTPUT_LINE();
        printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), content);
        return content;
    }
    int l = 0;
    if (content != lines) {
        lines--;
        length--;
        char *c = lines;
        while (*c != '\0') {
            *c = *(c + 1);
            c++;
            l++;
        }
    }
    CLEAR_OUTPUT_LINE();
    printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), content);
    if (lines - content != length) {
        MOVE_LEFT(l - 1);
    } else {
        MOVE_LEFT(l - 2);
    }
    return content;
}

Backspace *Backspace::getInstance() {
    if (instance == nullptr) {
        instance = new Backspace();
    }
    return instance;
}
