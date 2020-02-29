//
// Created by Isaac_Chen on 2020/2/29.
//

#include "Down.h"
#include <cstdio>
#include <unistd.h>
#include "KeyboardOperation.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Down *Down::instance = nullptr;

Down::Down() {

}

char *Down::onClick(char *&lines, Log &log, char *content, int &length, char *path) {
    *lines = '\0';
    char *searchResult = log.nextCommand(content);
    CLEAR_OUTPUT_LINE();
    if (searchResult != nullptr) {
        printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), searchResult);
    } else {
        printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), content);
    }
    lines = content + length;
    return searchResult;
}

Down *Down::getInstance() {
    if (instance == nullptr) {
        instance = new Down();
    }
    return instance;
}
