#ifndef CHAT_H
#define CHAT_H

#include "common.h"
#include "network.h"

enum chat_state
{
    Off,
    Slave,
    Master
};
typedef enum chat_state chat_state_t;
int parse_connect_command(char* command);
#endif