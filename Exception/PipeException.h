//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_PIPEEXCEPTION_H
#define SHELL_PIPEEXCEPTION_H
#include <exception>

class PipeException : public std::exception {
    const char *what() const throw() {
        return "Fail to create pipe.\n";
    }
};
#endif //SHELL_PIPEEXCEPTION_H
