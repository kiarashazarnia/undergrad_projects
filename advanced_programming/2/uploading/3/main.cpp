#include "header.h"

int main()
{
    vector<string> table;
    string path;
    int x, y;
    input_n_initial( table, x, y);
    path = solve( table, path, x, y);
    if(path.length() == 0)
        cout<<"NO SOLUTION"<<endl;
    else
        cout<<path<<endl;
    return 0;
}
