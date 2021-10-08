#ifndef GLOB
#define GLOB

#include <vector>
#include <semaphore.h>
#include <string>

using namespace std;

extern vector<vector<string>> data;
extern int maximum;
extern int counter_fst;
extern int counter_sec;
extern sem_t sem_max;
extern sem_t sem_count;
extern sem_t sem_bar;
extern int currentmax;
extern vector<int> max_vec;

#endif