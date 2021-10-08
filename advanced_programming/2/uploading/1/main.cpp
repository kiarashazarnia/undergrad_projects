#include "header.h"

int main()
{
    vector <Class> classes;
    int m, r, n;
    cin>>m>>r>>n;
    input(classes, m, r);
    cout<<needed_time(classes, n)<<endl;
    return 0;
}
