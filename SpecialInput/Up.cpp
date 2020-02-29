//
// Created by Isaac_Chen on 2020/2/29.
//

#include "Up.h"
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include "KeyboardOperation.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

Up *Up::instance = nullptr;

char *Up::onClick(char *&lines, Log &log, char *content, int &length, char *path) {
    *lines = '\0';
    char *searchResult = log.lastCommand(content);
    CLEAR_OUTPUT_LINE();
    if (searchResult != nullptr) {
        printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), searchResult);
        length = strlen(searchResult);
    } else {
        printf("\r(pid=%d)%s$ %s", getpid(), getcwd(path, MAX_PATH), content);
    }
    lines = content + length;
    return searchResult;
}

Up::Up() {

}

Up *Up::getInstance() {
    if (instance == nullptr) {
        instance = new Up();
    }
    return instance;
}
