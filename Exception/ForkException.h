//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_FORKEXCEPTION_H
#define SHELL_FORKEXCEPTION_H

#include <exception>

class ForkException : public std::exception {
    const char *what() const throw() {
        return "Fail to fork.\n";
    }
};

#endif //SHELL_FORKEXCEPTION_H
