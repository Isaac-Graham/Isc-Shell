//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_INPURFORMATEXCEPTION_H
#define SHELL_INPURFORMATEXCEPTION_H
#include <exception>

class InputFormatException : public std::exception {
    const char *what() const throw() {
        return "Invalid format\n";
    }
};
#endif //SHELL_INPURFORMATEXCEPTION_H
