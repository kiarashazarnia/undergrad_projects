#include <iostream>
#include <vector>
#include <string>

using namespace std;

void input_n_initial( vector<string> &table, int &x, int &y);
bool go_back( vector<string> &table, char direction, char past_state, int &x, int &y);
bool go_on( vector<string> &table, char direction, char &past_state, int &x, int &y);
string solve( vector<string> &table, string path, int &x, int &y);
