//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_BOUNDARYEXCEPTION_H
#define SHELL_BOUNDARYEXCEPTION_H
#include <exception>

class BoundaryException : public std::exception {
    const char *what() const throw() {
        return "The boundary is wrong.\n";
    }
};
#endif //SHELL_BOUNDARYEXCEPTION_H
