#ifndef COMMAND_H
#define COMMAND_H
#include "common.hpp"

#define LIKE 1
#define DISL -1
#define SEPRATE "__________________________________________________"
const bool log_enable = true;

namespace COMMAND{
    enum CommandName{
    signup = 0,
    login,
    logout,
    jeek,
    text,
    tag,
    mention,
    publish,
    abort,
    showJeek,
    search,
    comment,
    reply,
    rejeek,
    showComment,
    showReply,
    like,
    dislike,
    follow,
    unfollow,
    notifications,
    invalid
    };
};

struct CommandPack{
    string str;
    unsigned param;
};

using COMMAND::CommandName;

const vector<CommandPack> commands = {
    {"signup",3}
    ,{"login",2}
    ,{"logout",0}
    ,{"jeek",0}
    ,{"text",1}
    ,{"tag",1}
    ,{"mention",1}
    ,{"publish",0}
    ,{"abort",0}
    ,{"showJeek",1}
    ,{"search",1}
    ,{"comment",2}
    ,{"reply",2}
    ,{"rejeek",1}
    ,{"showComment",1}
    ,{"showReply",1}
    ,{"like",1}
    ,{"dislike",1}
    ,{"follow",1}
    ,{"unfollow",1}
    ,{"notifications",0}
    ,{"invalid",0}
};

bool isWhiteSpace(char c);
int firstPos(unsigned i, unsigned j);
int firstBlankPos(string s);
string splitFirstWord(string& str);
vector<string> splitStr(string str);

class Command{
public:
    void giveCommand();
    vector<string> split();
    string text();
    CommandName whatCommanded();
    int words();
    string fromWordNum(int num);
    void flush();
private:
    string command_line;
    vector<string> splitted_command;
};
 
#endif