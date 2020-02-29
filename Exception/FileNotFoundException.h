//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_FILENOTFOUNDEXCEPTION_H
#define SHELL_FILENOTFOUNDEXCEPTION_H
#include <exception>

class FileNotFoundException : public std::exception {
    const char *what() const throw() {
        return "File not exist or not found\n";
    }
};
#endif //SHELL_FILENOTFOUNDEXCEPTION_H
