#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string read_sensor(int sensor, char* path);

int main()
{
    char* path = "../databases/0/0.txt";
    int num;

    cin >> num;
    cout << read_sensor(num, path) << endl;
}

string read_sensor(int sensor, char* path)
{
    ifstream file;
    string line;
    string number;
    string value = "-1";
    
    file.open(path);
    while (getline(file, line))
    {
        number = line.substr(0, line.find(" "));
        if(number.compare(to_string(sensor)) == 0) 
        {
            value = line.substr(line.find(" ") + 1, line.size());
            break;
        }
    }
    file.close();
    return value;
}