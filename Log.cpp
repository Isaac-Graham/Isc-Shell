//
// Created by Isaac_Chen on 2020/2/22.
//

#include "Log.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include "Exception/IndexOutOfBoundException.h"

Log::Log() {
    this->head = nullptr;
    this->tail = nullptr;
    this->curr = nullptr;
}

Log::~Log() {
    free(this);
}

void Log::append(char *item) {
    LogElement *tmp = (LogElement *) malloc(sizeof(LogElement));
    if (tmp == NULL) exit(1);
    tmp->command = (char *) malloc(sizeof(char) * (strlen(item) + 1));
    if (tmp->command == NULL) exit(1);
    strcpy(tmp->command, item);
    tmp->next = NULL;
    if (this->head == NULL) { /* size == 0 */
        tmp->prev = NULL;
        this->head = tmp;
        this->tail = this->head;
    } else { /* size > 0 */
        tmp->prev = this->tail;
        this->tail->next = tmp;
        this->tail = this->tail->next;
    }
    LogElement *cur = new LogElement();
    cur->prev = tail;
    this->curr = cur;
}

char *Log::pop() {
    LogElement *le = this->tail;
    this->tail = this->tail->prev;
    this->tail->next = nullptr;
    this->curr->prev = this->tail;
    return le->command;
}

char *Log::at(unsigned int index) noexcept(false) {
    LogElement *le = head;
    for (int i = 0; i < index; i++) {
        if (le == nullptr) {
            throw IndexOutOfBoundException();
        }
        le = le->next;
    }
    if (le == nullptr) {
        throw IndexOutOfBoundException();
    }
    return le->command;
}

unsigned int Log::size() {
    LogElement *le = head;
    unsigned int cnt = 1;
    while (le != nullptr && le != tail) {
        cnt++;
        le = le->next;
    }
    return cnt;
}

char *Log::lastSimilarCommand(char *c) {
    while (head != nullptr && curr->prev != nullptr) {
        curr = curr->prev;
        if (match(c, curr->command)) {
            return curr->command;
        }
    }
    if (head == nullptr) {
        return nullptr;
    } else if (curr != nullptr) {
        if (match(c, curr->command)) {
            return curr->command;
        }
    }
    return nullptr;
}

char *Log::nextSimilarCommand(char *c) {
    while (tail != nullptr && curr->next != nullptr) {
        curr = curr->next;
        if (match(c, curr->command)) {
            return curr->command;
        }
    }
    return nullptr;
}

char *Log::lastCommand(char *c) {
    if (c == nullptr) {
        return lastUseCommand();
    } else {
        return lastSimilarCommand(c);
    }
}

char *Log::nextCommand(char *c) {
    if (c == nullptr) {
        return nextUseCommand();
    } else {
        return nextSimilarCommand(c);
    }
}

char *Log::lastUseCommand() {
    if (curr->prev != nullptr) {
        char *res = curr->prev->command;
        curr = curr->prev;
        return res;
    } else if (head != nullptr) {
        return head->command;
    } else {
        return nullptr;
    }
}

char *Log::nextUseCommand() {
    if (curr->next != nullptr) {
        char *res = curr->next->command;
        curr = curr->next;
        return res;
    } else {
        return nullptr;
    }
}

bool Log::match(const char *c1, const char *c2) {
    const char *currentCommandPointer = c2;
    while (*c1 != '\0') {
        if (*c1 != *currentCommandPointer) {
            return false;
        }
        c1++;
        currentCommandPointer++;
    }
    return true;
}


LogElement::LogElement() {
    this->command = nullptr;
    this->prev = nullptr;
    this->next = nullptr;
}

LogElement::LogElement(char *command) {
    this->command = command;
    this->prev = nullptr;
    this->next = nullptr;
}
