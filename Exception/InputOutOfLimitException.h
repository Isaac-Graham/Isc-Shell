//
// Created by Isaac_Chen on 2020/2/28.
//

#ifndef SHELL_INPUTOUTOFLIMITEXCEPTION_H
#define SHELL_INPUTOUTOFLIMITEXCEPTION_H


#include <exception>
#include <cstdlib>
#include <cstdio>

class InputOutOfLimitException : public std::exception {
    int limit = -1;
    char *buf = (char *) calloc(50, sizeof(char));
public:
    InputOutOfLimitException(int limit) {
        this->limit = limit;
    }

    InputOutOfLimitException() {}

    const char *what() const throw()//#1
    {
        if (limit != -1) {
            snprintf(buf, 49, "InputOutOfLengthLimit: limit: %d", limit);
            return buf;
        } else {
            return "InputOutOfLengthLimit";
        }
    }
};


#endif //SHELL_INPUTOUTOFLIMITEXCEPTION_H
