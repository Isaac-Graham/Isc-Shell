//
// Created by Isaac_Chen on 2020/2/22.
//

#include "PreserveCommand.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int ChangeDirectory::run(char *command, char *arg) {
    if (!arg || strcmp(arg, "~") == 0) {
        char *home;
        home = getenv("HOME");
        arg = home;
    }
    if (chdir(arg) != 0) {
        perror("Fail to change directory");
        return FAIL;
    }
    return SUCCESS;
}

int Echo::run(char *command, char *arg) {
    if (!arg) {
        return FAIL;
    }
    if (*arg != '$') {
        printf("%s\n", arg);
        return SUCCESS;
    } else {
        arg++;
        char *env = getenv(arg);
        if (env == nullptr) {
            printf("Invalid Argument\n");
            return FAIL;
        } else {
            printf("%s\n", getenv(arg));
            return SUCCESS;
        }
    }
    return SUCCESS;
}
