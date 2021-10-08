#include "user.h"
#include "utility.h"
#include <stdlib.h>

user_t* new_user()
{
    user_t* newu = (user_t*) malloc(sizeof(user_t));
    if(newu == NULL)
        error_log("newuser");
    
    newu -> username = NULL;
    newu -> diamond = 0;
    newu -> introduced = false;
    newu -> credit = 0;
    return newu;
}