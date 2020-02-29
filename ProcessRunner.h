//
// Created by Isaac_Chen on 2020/2/28.
//

//#define ERROR_FORK -1
//#define ERROR_BOUND -2
//#define ERROR_INPUT -3
//#define ERROR_PIPE -4
#define ERROR_PARAMETER_MISS -5
#define PIPE '|'
#define COMMAND_IN '<'
#define COMMAND_OUT '>'
#define EXIT -1
#define NORMAL_RESULT 0
#define MAX_ARGV 16
#define BUF 4096


#ifndef SHELL_PROCESSRUNNER_H
#define SHELL_PROCESSRUNNER_H


class ProcessRunner {
    char *inputCommand;
    int length;

    int callCommand(int left, int right);

    int callCommandWithRedirection(int left, int right);
public:
    ProcessRunner();

    ProcessRunner(char *commands, const int length);

    int callCommandWithPipe(int left, int right);

};


#endif //SHELL_PROCESSRUNNER_H
