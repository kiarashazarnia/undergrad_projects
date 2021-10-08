#include <iostream>
#include <vector>

using namespace std;

struct Class
{
    int number;
    int time;
    vector<int> prereq;
};

void input(vector<Class> &classes, int m, int r);
int needed_time(const vector<Class> &classes, int required_class);
