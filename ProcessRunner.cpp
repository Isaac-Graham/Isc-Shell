//
// Created by Isaac_Chen on 2020/2/28.
//

#include <cstring>
#include "ProcessRunner.h"
#include "PreserveCommand.h"
#include <cstdlib>
#include <unistd.h>
#include <wait.h>
#include <cstdio>
#include "Exception/BoundaryException.h"
#include "Exception/ForkException.h"
#include "Exception/InpurFormatException.h"
#include "Exception/PipeException.h"
#include "Exception/FileNotFoundException.h"

ProcessRunner::ProcessRunner() {}

ProcessRunner::ProcessRunner(char *commands, const int length) {
    this->inputCommand = commands;
    this->length = length;
}

int ProcessRunner::callCommand(int left, int right) {
    char command[right - left + 1];
    for (int i = left; i < right; i++) {
        command[i - left] = inputCommand[i];
    }
    command[right - left] = '\0';

    char *cmd = strtok(command, " ");
    char *argv[MAX_ARGV];
    argv[0] = cmd;
    for (int i = 1; i < MAX_ARGV; i++) {
        char *singleArg = strtok(NULL, " ");
        if (singleArg == nullptr) {
            argv[i] = NULL;
            break;
        }
        argv[i] = singleArg;
    }

    if (strcmp(cmd, "cd") == 0) {
        PreserveCommand *cd = new ChangeDirectory();
        return cd->run(cmd, argv[1]);
    } else if (strcmp(cmd, "exit") == 0) {
        return EXIT;
    } else if (strcmp(cmd, "echo") == 0) {
        PreserveCommand *echo = new Echo();
        return echo->run(cmd, argv[1]);
    } else {
        pid_t pid;
        if ((pid = fork()) < 0) { /* failed to create a process */
            throw ForkException();
        } else if (pid == 0) { /* child process */
            if (execvp(cmd, argv) == -1) {
                printf("Isc-Shell: command not found: %s\n", cmd);
                exit(0);
            }
        } else if (pid > 0) { /* father process */
            waitpid(pid, NULL, 0);
        }
    }
    return SUCCESS;
}


int ProcessRunner::callCommandWithRedirection(int left, int right) {
    int inNum = 0, outNum = 0;
    char *inFile = NULL, *outFile = NULL;
    int endIdx = right; // 指令在重定向前的终止下标
    bool appendOutput = false;
    for (int i = left; i < right; ++i) {
        if (inputCommand[i] == COMMAND_IN) { // 输入重定向
            ++inNum;
            if (i + 1 < right) {
                inFile = inputCommand + i + 1;
            } else {
                throw InputFormatException();
            }
            if (endIdx == right) endIdx = i;
        } else if (inputCommand[i] == COMMAND_OUT) { // 输出重定向
            ++outNum;
            if (i + 1 < right && inputCommand[i + 1] == COMMAND_OUT) {
                appendOutput = true;
                ++i;
            }
            if (i + 1 < right) {
                outFile = inputCommand + i + 1;
            } else {
                throw InputFormatException();
            } // 重定向符号后缺少文件名
            if (endIdx == right) endIdx = i;
        }
    }
//    if(inNum == 0 && inNu)



    while (outFile != nullptr && *outFile == ' ') {
        outFile++;
    }
    while (inFile != nullptr && *inFile == ' ') {
        inFile++;
    }

    if (inNum == 1) {
        FILE *fp = fopen(inFile, "r");
        if (fp == NULL)
            throw FileNotFoundException();
        fclose(fp);
    }
    if (inNum > 1) {
        throw InputFormatException();
    } else if (outNum > 1) {
        throw InputFormatException();
    }

//    int result = NORMAL_RESULT;
    pid_t pid = fork();
    if (pid == -1) {
        throw ForkException();
    } else if (pid == 0) {
        printf("\n");
        if (inNum == 1) {
            freopen(inFile, "r", stdin);
        }
        if (outNum == 1) {
            if (!appendOutput) {
                freopen(outFile, "w", stdout);
            } else {
                freopen(outFile, "a+", stdout);
            }
        }
        int result = callCommand(left, endIdx);
        freopen("/dev/tty", "r", stdin);
        freopen("/dev/tty", "w", stdout);
        exit(result);
    } else if (pid > 0) { /* father process */
        waitpid(pid, NULL, 0);
    }
    return SUCCESS;
}

int ProcessRunner::callCommandWithPipe(int left, int right) {
    if (left > right) {
        throw BoundaryException();
    }

    int pipeIndex = -1;
    for (int i = left; i < right; i++) {
        if (inputCommand[i] == PIPE) {
            pipeIndex = i;
            break;
        }
    }
    if (pipeIndex == -1) {
        return callCommandWithRedirection(left, right);
//        return callCommand(left, right);
    } else if (pipeIndex + 1 == right) {
        throw InputFormatException();
    } else {
        int fds[2];
        if (pipe(fds) == -1) {
            throw PipeException();
        }
        int result = NORMAL_RESULT;
        pid_t pid = vfork();
        if (pid == -1) {
            throw ForkException();
        } else if (pid == 0) {
            close(fds[0]);
            int saveOut = dup(STDOUT_FILENO);
            dup2(fds[1], STDOUT_FILENO);
            close(fds[1]);

            result = callCommandWithRedirection(left, pipeIndex);
            //callCommand(left, pipeIndex);
            dup2(saveOut, 1);
            close(saveOut);
            exit(result);
        } else {
            int status;
            waitpid(pid, &status, 0);
            int exitCode = WEXITSTATUS(status);
            if (exitCode != NORMAL_RESULT) {
                char info[BUF] = {0};
                char line[BUF];
                close(fds[1]);
                int saveIn = dup(STDIN_FILENO);
                dup2(fds[0], STDIN_FILENO);
                close(fds[0]);
                while (fgets(line, BUF, stdin) != NULL) {
                    strcat(info, line);
                }
                dup2(saveIn, STDIN_FILENO);
                close(saveIn);
                printf("%s", info);
                result = exitCode;
            } else if (pipeIndex + 1 < right) {
                close(fds[1]);
                int saveIn = dup(STDIN_FILENO);
                dup2(fds[0], STDIN_FILENO);
                close(fds[0]);
                result = callCommandWithPipe(pipeIndex + 1, right);
                dup2(saveIn, STDIN_FILENO);
                close(saveIn);

            }
        }
        return result;
    }
}


