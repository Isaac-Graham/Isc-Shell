//
// Created by Isaac_Chen on 2020/2/22.
//
#include <cstring>
#include "PreserveCommand.h"
#include "Log.h"
#include <unistd.h>
#include <cstdio>
#include "ProcessRunner.h"
#include "Reader.h"
#include "Exception/InputOutOfLimitException.h"
#include <csignal>

#define MAX_CMD 512
#define MAX_PATH 512
#define MAX_ARGV 16


void initCMD(char *l) {
    for (int i = 0; i < MAX_CMD; i++) {
        l[i] = '\0';
    }
}

void signalHandlerExitParent(int signum) {
    printf("\r");
}

int main() {
    signal(SIGINT, signalHandlerExitParent);
    char line[MAX_CMD];
    char path[MAX_PATH];
    Log *log_t = new Log();
    while (strcmp(line, "exit") != 0) {
        initCMD(line);
        printf("(pid=%d)%s$ ", getpid(), getcwd(path, MAX_PATH));
        Reader *reader = Reader::getInstance();

        int length = 0;
        try {
            int l = reader->getInputCommand(line, *log_t, path);
            length = l;
        } catch (InputOutOfLimitException &e) {
            printf("%s", e.what());
        }
        log_t->append(line);
        if (line[0] == '\0') continue;
        try {
            ProcessRunner *pr = new ProcessRunner(line, length);
            pr->callCommandWithPipe(0, length);
        } catch (std::exception &e) {
            printf("%s", e.what());
        }
    }
    log_t->~Log();
    return 0;
}