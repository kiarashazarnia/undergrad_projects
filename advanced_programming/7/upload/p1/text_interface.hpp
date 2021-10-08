#ifndef TXTINTFS_H
#define TXTINTFS_H

#include "command.hpp"
#include "implementation.hpp"

typedef void* Function (void);

class TextInterface{
public:
    void validate_input();
    void signup();
    void login();
    void logout();
    void newJeek();
    void text();
    void tag();
    void mention();
    void publish();
    void abortJeek();
    void search();
    void comment();
    void reply();
    void rejeek();
    void showJeek();
    void showComment();
    void showReply();
    void like();
    void dislike();
    void follow();
    void unfollow();
    void notifications();
    void run();
    void flushCommand();
private:
    Implementation implement;
    vector<string> input;
    Command running_command;
    CommandName command_name;
};

void printJeeks(vector<Jeek>& jeeks);
void printStrings(vector<string>& strings);

#endif