#include "chat.h"

int parse_connect_command(char* command)
{
    char* string = strdup(command); 
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
    if(equals(request, CONNECT) && parameter != NULL)
    {
        return atoi(parameter);
    }
    return NULL;
}
