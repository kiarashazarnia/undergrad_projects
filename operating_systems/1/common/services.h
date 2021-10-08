#ifndef SERVICES_H
#define SERVICES_H
#include "common.h"
#include "values.h"
#include "user.h"
#include "network.h"
#include "string.h"
#include "utility.h"
#include "network.h"
#include "competition.h"

struct session
{
    user_t* user;
    state_t state;
    sockaddr_in_t* address;
    struct session* next;
};
typedef struct session session_t;

static session_t* session_list_head = NULL;

enum command
{
    CommandLogin,
    CommandDiamond,
    CommandCredit,
    CommandChat,
    CommandWhit,
    CommandDisconnect,
    CommandCompete,
    CommandIntroducer,
    CommandAnswer,
    CommandHelp,
    CommandInvalid
};
typedef enum command command_t;

char* report_massage();
void parse(char* string, char** request, char** parameter);
char* service(sockaddr_in_t client_address, char* buffer, int qindex, competition_state_t competition_state);
command_t what_commanded(char* request);
session_t* find_session_by_address(sockaddr_in_t* address);
session_t* find_session_by_username(char* username);
bool address_exists(sockaddr_in_t* address);
bool username_exists(sockaddr_in_t* username);
session_t* make_session(sockaddr_in_t* address);
void add_session(session_t* session);
char* address_of(char* username);
char* chat_list(char* username);
void finish_competition();

#endif
