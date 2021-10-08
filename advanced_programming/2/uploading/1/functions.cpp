#include "header.h"

void input(vector<Class> &classes, int m, int r)
{
    // c1 is a prereguisite for c2.
    int c1, c2;
    Class temp;
    for(int i=0; i<m; i++)
    {
        temp.number = i;
        cin>>temp.time;
        classes.push_back(temp);
    }

    for(int i=0; i<r; i++)
    {
        cin>>c1>>c2;
        classes[c2].prereq.push_back(c1);
    }
}

int needed_time( const vector<Class> &classes, int required_class)
{
    int require_time = 0;
    int path_time;
    int prerequisites_quantity = classes[required_class].prereq.size();
    for(int i=0; i<prerequisites_quantity; i++)
    {
        path_time = needed_time( classes, classes[required_class].prereq[i]);
        if( path_time > require_time)
            require_time = path_time;
    }
    return require_time + classes[required_class].time;
}
