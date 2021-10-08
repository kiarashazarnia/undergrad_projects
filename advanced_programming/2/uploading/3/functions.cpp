//#Kiarash Azarnia 810195576

#include "header.h"
#include <cstdio>

#define table(x,y) (table[y].at(x))

void input_n_initial( vector<string> &table, int &x, int &y)
{
	char temp;
	string row;
	int i = 0, j = 0;
	temp = getchar();
	while(temp != EOF)
	{
		switch( temp)
		{
			case '\n':
				table.push_back( row);
				row.erase();
				j++;
				i=0;
			break;
			case 'S':
				x=i; y=j;
			default:
				row.push_back( temp);
				i++;
			break;
		}
		temp = getchar();
	}
	table(x,y) = '*';
}

bool go_back( vector<string> &table, char direction, char past_state, int &x, int &y)
{
	if(!( x == table[0].length() || y == table.size() || x<0 || y<0))
		if ( table(x,y) != '#')
			table(x,y) = past_state;

	switch( direction)
	{
		case 'U':
			y++;
		break;
		case 'R':
			x--;
		break;
		case 'D':
			y--;
		break;
		case 'L':
			x++;
		break;
	}
}

bool go_on( vector<string> &table, char direction, char& past_state, int &x, int &y)
{
	switch( direction)
	{
		case 'U':
			y--;
		break;
		case 'R':
			x++;
		break;
		case 'D':
			y++;
		break;
		case 'L':
			x--;
		break;
	}
	if( x == table[0].length() || y == table.size() || x<0 || y<0)
		return 0;
	past_state = table(x,y);
	if ( table(x,y) == '#' || table(x,y) == '*')
		return 0;
    if( table(x,y) != 'E')
        table(x,y) = '*';
	return 1;
}

string solve( vector<string> &table, string path, int &x, int &y)
{
	if( table(x,y) == 'E')
		return path;

	string guessing_path = path, true_path;
	char past_state, direction[4] = {'U','R','D','L'};
	for(int i=0; i<4; i++)
	{
		if( go_on( table, direction[i], past_state, x, y))
		{
            guessing_path.push_back( direction[i]);
			true_path = solve(table, guessing_path, x, y);
			if( table(x,y) == 'E')
				return true_path;
			else
			{
				if(guessing_path.length())
					guessing_path.erase(guessing_path.end()-1);
				go_back(table, direction[i], past_state, x, y);
			}
		}
		else{
			go_back(table, direction[i], past_state, x, y);
		}
	}
	return "";
}
