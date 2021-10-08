#include "services.h"

char* service(sockaddr_in_t client_address, char* string, int qindex, competition_state_t competition_state)
{
    session_t* session = find_session_by_address(&client_address);
    if(session == NULL)
    {
        session = make_session(&client_address);
        add_session(session);
    }
    
    char* request;
    char* parameter;
    request = strsep(&string, SPACE);
    if(string == NULL || strlen(string) <= 1)
    {
        parameter = NULL;
        request[strlen(request) - 1] = END;
    }
    else 
    {
        parameter = strdup(string);
        parameter[strlen(parameter) - 1] = END;
    }
    switch (what_commanded(request))
    {
        
        case CommandLogin:
            if(session -> state == Idle)
            {
                if(parameter == NULL)
                {
                    server_log(MSG_INVALID_INPUT);
                    return MSG_INVALID_INPUT;
                }
                if(username_exists(parameter))
                {
                    server_log(MSG_DUPLICATED_USERNAME);
                    return MSG_DUPLICATED_USERNAME;
                }
                session -> user -> username = strdup(parameter);
                session -> state = Work;
                server_log(LOG_LOGIN_SUCCESS);
                return MSG_LOGIN_SUCCESS;
            }
            else
            {
                server_log(LOG_LOGIN_FAIL);
                return MSG_LOGEDIN_BEFORE;
            }
        
        case CommandDiamond:
            if(session -> state == Idle)
                return MSG_LOGIN_FIRST;
            server_log(LOG_DIAMOND_REP);
            return itos(session -> user -> diamond);
        
        case CommandCredit:
            if(session -> state == Idle)
                return MSG_LOGIN_FIRST;
            server_log(LOG_CREDIT_REP);
            return itos(session -> user -> credit);
        
        case CommandChat:
            if(session -> state == Idle)
                return MSG_LOGIN_FIRST;
            server_log(LOG_CHAT_REP);
            session -> state = Chat;
            return chat_list(session -> user -> username);
        
        case CommandWhit:
            if(session -> state != Chat)
                return MSG_CHAT_FAILED;
            server_log(LOG_ADDR_REP);
            return address_of(parameter);
        
        case CommandDisconnect:
            if(session -> state != Chat)
                return MSG_NOT_IN_CHAT;   
            session -> state = Work;
            return MSG_SUCCESS;

        case CommandCompete:
            if(session -> state == Idle)
                return MSG_LOGIN_FIRST;
            if(competition_state == Lock || competition_state == Run)
            {
                return MSG_LATE_REG;
            }
            session -> state = Compete;
            session -> user -> answers = 0;
            server_log(LOG_REGIS_REP);
            return MSG_COMPETE_SUCCESS;
        
        case CommandIntroducer:
            if(session -> state == Idle)
                return MSG_LOGIN_FIRST;
            if(session -> user -> introduced)
                return MSG_INTRODUCED_BEFORE;
            server_log(LOG_INTRO_REP);    
            session -> user -> introduced = true;
            find_session_by_username(parameter) -> user -> diamond += AWARD;
            return MSG_INTRODUCED_SUCCESS;
        
        case CommandAnswer:
            if(session -> state != Compete)
                return MSG_NOT_COMPETE;
            server_log(LOG_ANS_REP);
            if(atoi(parameter)-1 == get_answer(qindex-1))
            {
                session -> user -> answers++;
                return MSG_CORRECT_ANS;
            }
            else
            {
                if(session -> user -> diamond > 0)
                {
                    session -> user -> answers++;
                    session -> user -> diamond--;
                    return MSG_WRONG_ANS_DIAMOND;
                }
                else
                {
                    session -> state = Work;
                    return MSG_WRONG_ANS_FAIL;
                }
            }
        
        case CommandHelp:
            server_log(LOG_HELP_REP);
            return MSG_HELP;
        break;

        case CommandInvalid:
        default:
            server_log(LOG_INVALID_COMMAND);
            return MSG_INVALID_COMMAND;
        break;
    }
}

void parse(char* string, char** request, char** parameter)
{
    char* str = strdup(string); 
    (*request) = strdup(strsep(&str, SPACE));
    (*parameter) = strdup(strsep(&str, SPACE));
}

command_t what_commanded(char* request)
{
    if(request == NULL)
        return CommandInvalid;
    if(equals(request, LOGIN))
        return CommandLogin;
    if(equals(request, DIAMOND))
        return CommandDiamond;
    if(equals(request, CREDIT))
        return CommandCredit;
    if(equals(request, CHAT))
        return CommandChat;
    if(equals(request, WITH))
        return CommandWhit;
    if(equals(request, COMPETE))
        return CommandCompete;
    if(equals(request, INTRODUCER))
        return CommandIntroducer;
    if(equals(request, ANSWER))
        return CommandAnswer;
    if(equals(request, HELP))
        return CommandHelp;
    return CommandInvalid;
}


session_t* find_session_by_address(sockaddr_in_t* address)
{
    if(address == NULL)
        return NULL;
    session_t* pointer = session_list_head;
    while(pointer)
    {
        if(pointer -> address -> sin_port == address -> sin_port)
            return pointer;
        pointer = pointer -> next;
    }
    return NULL;
}

session_t* find_session_by_username(char* username)
{
    if(username == NULL)
        return NULL;
    session_t* pointer = session_list_head;
    while(pointer)
    {
        if(equals(pointer -> user -> username, username))
            return pointer;
        pointer = pointer -> next;
    }
    return NULL;
}

bool address_exists(sockaddr_in_t* address)
{
    return find_session_by_address(address) != NULL;
}

bool username_exists(sockaddr_in_t* username)
{
    return find_session_by_username(username) != NULL;
}

session_t* make_session(sockaddr_in_t* address)
{
    session_t* new_session = malloc(sizeof(session_t));
    new_session -> next = NULL;
    new_session -> state = Idle;
    new_session -> user = new_user();
    new_session -> address = malloc(sizeof(address));
    
    bzero(new_session -> address, sizeof(address)); 
	new_session -> address -> sin_family = address -> sin_family;
	(new_session -> address -> sin_addr).s_addr = address -> sin_addr.s_addr; 
	new_session -> address -> sin_port = address -> sin_port;
    return new_session;
}

void add_session(session_t* session)
{
    if(session_list_head == NULL)
    {
        session_list_head = session;
        return;
    }
    session_t* pointer = session_list_head;
    while(pointer -> next != NULL)
    {
        pointer = pointer -> next;
    }
    pointer -> next = session;
}

char* chat_list(char* username)
{
    static char list[MAXLINE];
    bzero(list, MAXLINE);
    strcpy(list, CHAT_LIST);
    session_t* pointer = session_list_head;
    while(pointer)
    {
        if(!equals(pointer -> user -> username, username))
        {
            strcat(list, pointer -> user -> username);
            strcat(list, "\n");
        }
        pointer = pointer -> next;
    }
    return list;
}

char* address_of(char* username)
{
    session_t* session = find_session_by_username(username);
    int port = session -> address -> sin_port;
    return itos(port);
}

int count_winners()
{
    int winners = 0;
    session_t* pointer = session_list_head;
    while(pointer)
    {
        winners += pointer -> user -> answers == QUESTIONS;
        pointer = pointer -> next;
    }
    return winners;
}

char* report_massage()
{
    int winners = count_winners();
    static char msg[LEN];
    bzero(msg, LEN);
    strcpy(msg, "number of winners is ");
    strcat(msg, itos(winners));
    return msg;
}

void finish_competition()
{
    int winners = count_winners();
    server_log(LOG_FINICH_COMP);
    if(winners == 0)
        return;
    int share = award / winners;
    session_t* pointer = session_list_head;
    while(pointer)
    {
        if(pointer -> state == Compete)
            pointer -> state = Work;
        if(pointer -> user -> answers == QUESTIONS)
            pointer -> user -> credit += share;
        pointer = pointer -> next;
    }
}