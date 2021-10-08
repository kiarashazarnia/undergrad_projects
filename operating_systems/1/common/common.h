#ifndef COMMON_H
#define COMMON_H

#define true    1
#define false   0
typedef int bool;

#define stdinfd     0
#define stdoutfd    1
#define stderrfd    2

#define FAIL    -1
#define LEN     100
#define BPORT   5050
#define MAXLINE 1024 
#define AWARD   10

#define DELAY                   10
#define SEC10                   10
#define REGISTER_DELAY          20
#define COMPETITION_INTERVAL    60

#define LH          "127.0.0.1"
#define END         '\0'
#define SPACE       " " 

#define LOGIN       "login"
#define DIAMOND     "diamond"
#define CREDIT      "credit"
#define CHAT        "chat"
#define COMPETE     "compete"
#define WITH        "with"
#define INTRODUCER  "introducer"
#define DISCONNECT  "disconnect"
#define DISCONNECTN "disconnect\n"
#define ANSWER      "answer"
#define CONNECT     "connect"
#define HELP        "help"

#define MSG_INVALID_INPUT       "invalid input"
#define MSG_DUPLICATED_USERNAME "duplicated username"
#define MSG_LOGIN_SUCCESS       "login successful"
#define MSG_LOGEDIN_BEFORE      "loggedin before"
#define MSG_LOGIN_FIRST         "please: login [username]"
#define MSG_COMPETE_SUCCESS     "competition register successful"
#define MSG_INTRODUCED_BEFORE   "introduced before"
#define MSG_INTRODUCED_SUCCESS  "introduced successful"
#define MSG_CHAT_SUCCESS        "chat success"    
#define MSG_CHAT_FAILED         "chat failed"
#define MSG_NOT_IN_CHAT         "not in chat"
#define MSG_INVALID_COMMAND     "invalid command to see commands input help"
#define MSG_WRONG_ANS           "wrong answer"
#define MSG_WRONG_ANS_DIAMOND   "wrong answer lost diamond"
#define MSG_WRONG_ANS_FAIL      "wrong answer competition fail"
#define MSG_CORRECT_ANS         "correct answer"
#define MSG_NOT_COMPETE         "not in competition"
#define MSG_INFORM_COMPETE      "competition is starting soon"
#define MSG_WARN_COMPETE        "register to competition sooner"
#define MSG_START_COMPETE       "competition start"
#define MSG_END_COMPETE         "competition end"
#define MSG_BROADCASTING        "broadcasting"
#define MSG_CORRECT_ANSWER      "correct answer is "
#define MSG_CONNECTED_TO        "connected to "
#define MSG_SUCCESS             "success"
#define MSG_LATE_REG            "late for register in this competition!"

#define MSG_HELP "\
***************************************************************\n\
*        Welcome to osQ knowledge chalenge                    *\n\
*        list of commands:                                    *\n\
*        login [username]      to login to chalenge           *\n\
*        diamond               to see your diamond            *\n\
*        credit                to see your credit             *\n\
* (chat) chat                  to see online people           *\n\
* (chat) with [your friend]    to get your friend's port      *\n\
* (chat) connect [port]        to connect to your friend      *\n\
* (chat) disconnect            exit chat                      *\n\
*        compete               to register in the competition *\n\
*        introducer [username] to identify your introducer    *\n\
*        answer [item number]  answer questions               *\n\
*        help                  to get help!                   *\n\
***************************************************************"

#define CHAT_LIST   "online users:\n"

#define LOG_LOGIN_SUCCESS   "login success"
#define LOG_LOGIN_FAIL      "login failure"
#define LOG_DIAMOND_REP     "diamond request"
#define LOG_CREDIT_REP      "credit request"
#define LOG_CHAT_REP        "chat request"
#define LOG_ADDR_REP        "address request"
#define LOG_REGIS_REP       "register request"
#define LOG_INTRO_REP       "introducer request"
#define LOG_ANS_REP         "answer request"
#define LOG_HELP_REP        "help request"
#define LOG_INVALID_COMMAND "invalid command"
#define LOG_FINICH_COMP     "competition finished"

#endif