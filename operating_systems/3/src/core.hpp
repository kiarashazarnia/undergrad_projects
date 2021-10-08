#include <iostream>
#include <vector>
#include <semaphore.h>
#include <fstream>

#define NUMBER 10
#define LEVEL 20
#define SLP 2

using namespace std;

vector<vector<string>> read_data(string path);
void print_vec(const vector<vector<string>>& vec);

class ThreadSense 
{ 
public:
    void operator()(int trdnum);
    void run(int trdnum, int level, ofstream& log);
    void barrier_fst(ofstream& log, int trdnum, int level); 
    void barrier_sec(ofstream& log, int level); 
}; 

void sems_init();