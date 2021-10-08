#include "competition.h"

const int award = AWARD;
const char question[QUESTIONS][LEN] = {
    "\n1\tWhich one is not a product of Apple?\n\t1. iPod       2. iCam        3. iPhone",
    "\n2\tWho is the creator of Linux?\n\t1. Linus      2. Bill        3. Steve",
    "\n3\tGnu is not ... ?\n\t1. unix       2. linux       3. free",
    "\n4\tWhich one is widly used by Google?\n\t1. IE         2. AI          3. Yahoo",
    "\n5\tWhere is the live repository of linux now?\n\t1. github      2. gitlab       3. bitbucket"
};
const int answer[QUESTIONS] = {
    1,
    0,
    0,
    1,
    1
};

int get_answer(int qindex)
{
    return answer[qindex];
}
