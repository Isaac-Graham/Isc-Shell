//
// Created by Isaac_Chen on 2020/2/28.
//

#include "Reader.h"
#include <termios.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "SpecialInput/Up.h"
#include "SpecialInput/Down.h"
#include "SpecialInput/Left.h"
#include "SpecialInput/Right.h"
#include "SpecialInput/BackSpace.h"
#include "Exception/InputOutOfLimitException.h"

Reader *Reader::instance = nullptr;

Reader::Reader() {
}

Reader *Reader::getInstance() {
    if (Reader::instance == nullptr) {
        Reader::instance = new Reader();
    }
    return Reader::instance;
}

char Reader::get1char() {

#ifdef _WIN32
    // Do nothing
#else   // store and modify the argument of terminal
    struct termios stored_settings;
    struct termios new_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
#endif

    int ret = 0;
    char c;

#ifdef _WIN32
    c = getch();
#else
    c = getchar();
#endif
#ifdef _WIN32
    // Do nothing
#else
    tcsetattr(0, TCSANOW, &stored_settings);
#endif

    return c;
}

void setData(char *&lines, char *&updatedCommand, char *&content) {
    if (updatedCommand != nullptr) {
        strcpy(content, updatedCommand);
        lines = content + strlen(content);
        updatedCommand = nullptr;
    }
}

int Reader::getInputCommand(char *lines, Log &log, char *path) {

    char *content = lines;
    char c;
    int length = 0;
    char *updatedCommand = nullptr;
    while ((c = get1char()) != '\n') {
        if (length > MAX_CMD) {
            throw InputOutOfLimitException(MAX_CMD);
        }
        if ((int) c == 127) {
            setData(lines, updatedCommand, content);
            SpecialInput *backspace = Backspace::getInstance();
            content = backspace->onClick(lines, log, content, length, path);
        } else if (c == '\033') {
            // Input the direction button
            if ((c = get1char()) == '[') {
                if ((c = get1char()) == 'A') {
                    SpecialInput *up = Up::getInstance();
                    updatedCommand = up->onClick(lines, log, content, length, path);
                } else if (c == 'B') {
                    SpecialInput *down = Down::getInstance();
                    updatedCommand = down->onClick(lines, log, content, length, path);
                } else if (c == 'C') {
                    setData(lines, updatedCommand, content);
                    SpecialInput *right = Right::getInstance();
                    right->onClick(lines, log, content, length, path);
                } else if (c == 'D') {
                    setData(lines, updatedCommand, content);
                    SpecialInput *left = Left::getInstance();
                    left->onClick(lines, log, content, length, path);
                }
            }
        } else {
            setData(lines, updatedCommand, content);
            length++;
            *lines = c;
            lines++;
        }
    }

    setData(lines, updatedCommand, content);
//    *lines = '\0';
    lines = content;
    return length;
}


