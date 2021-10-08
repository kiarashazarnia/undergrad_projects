#include "global.hpp"
#include "core.hpp"

vector<vector<string>> data;
int maximum = -1;
int currentmax = -1;
int counter_fst = 0;
int counter_sec = 0;
vector<int> max_vec(LEVEL);
sem_t sem_max;
sem_t sem_count;
sem_t sem_bar;