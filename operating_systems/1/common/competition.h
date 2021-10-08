#ifndef COMPETE_H
#define COMPETE_H

#include "common.h"
#include "user.h"

#define COMPETITIONS    2
#define QUESTIONS       5
#define LEN             120

enum competition_state_e
{
    Wait,
    Inform,
    Lock,
    Run
};


extern const int award;
extern const char question[QUESTIONS][LEN];
extern const int answer[QUESTIONS];

typedef enum competition_state_e competition_state_t;
int get_answer(int qindex);

#endif