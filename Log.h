//
// Created by Isaac_Chen on 2020/2/22.
//
#include <vector>
#ifndef SHELL_LOG_H
#define SHELL_LOG_H

class LogElement {
public:
    char *command;
    LogElement *prev;
    LogElement *next;

    explicit LogElement(char *command);

    LogElement();
};

class Log {
private:

    char *lastSimilarCommand(char *c);

    char *nextSimilarCommand(char *c);

    char *lastUseCommand();

    char *nextUseCommand();

    bool match(const char *c1, const char *c2);

public:
    LogElement *head;
    LogElement *tail;
    LogElement *curr;

    Log();

    ~Log();

    void append(char *c);

    char *pop();

    char *at(unsigned int index) noexcept(false);

    unsigned int size();

    char *lastCommand(char *c);

    char *nextCommand(char *c);
};


#endif //SHELL_LOG_H
