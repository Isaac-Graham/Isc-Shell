//
// Created by Isaac_Chen on 2020/2/22.
//

#define FAIL -1
#define SUCCESS 0

#ifndef SHELL_PRESERVECOMMAND_H
#define SHELL_PRESERVECOMMAND_H


class PreserveCommand {
public:
    virtual int run(char *command, char *arg) = 0;
};

class ChangeDirectory : public PreserveCommand {
public:
    int run(char *command, char *arg) override;
};

class Echo : public PreserveCommand {
public:
    int run(char *command, char *arg) override;
};

#endif //SHELL_PRESERVECOMMAND_H
