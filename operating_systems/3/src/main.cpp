#include <iostream>
#include <thread>
#include <semaphore.h>
#include <assert.h>
#include "core.hpp"
#include "global.hpp"

using namespace std;

int main()
{
    data = read_data("inputs/inputs.txt");
    print_vec(data);
    assert(data.size() == NUMBER && data[0].size() == LEVEL);

    sems_init();
    thread* trd[NUMBER];
    for(int trdnum = 0; trdnum < NUMBER; trdnum++)
    {
        trd[trdnum] = new thread(ThreadSense(), trdnum);
    }

    for(int trdnum = 0; trdnum < NUMBER; trdnum++)
    {
        trd[trdnum] -> join();
    }

    return 0;
}