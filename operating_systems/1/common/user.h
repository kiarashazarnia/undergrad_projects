#ifndef USER_H
#define USER_H
#include "common.h"

enum state 
{
    Idle,
    Work,
    Compete,
    Chat
};
typedef enum state state_t;

struct user
{
    char* username;
    int diamond;
    bool introduced;
    int credit;
    int answers;
};
typedef struct user user_t;

user_t* new_user();

#endif