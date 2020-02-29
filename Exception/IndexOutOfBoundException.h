//
// Created by Isaac_Chen on 2020/2/28.
//

#ifndef SHELL_INDEXOUTOFBOUNDEXCEPTION_H
#define SHELL_INDEXOUTOFBOUNDEXCEPTION_H


#include <exception>

class IndexOutOfBoundException : public std::exception {
    const char *what() const throw() {
        return "IndexOutOfBound\n";
    }
};


#endif //SHELL_INDEXOUTOFBOUNDEXCEPTION_H
