#include "core.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <chrono>
#include <thread>
#include "global.hpp"


vector<vector<string>> read_data(string path)
{
    vector<vector<string>> result;
    string line;
    ifstream in;
    in.open(path);
    vector<string> temp;
    while(getline(in, line))
    {
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        boost::split(temp, line, boost::is_any_of(","));
        result.push_back(temp);
    }
    in.close();
    return result;
}

void print_vec(const vector<vector<string>>& vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << "\t";
        cout << endl;
    }
}

void ThreadSense::barrier_fst(ofstream& log, int trdnum, int level)
{
    sem_wait(&sem_count);
    counter_fst++;
    if(counter_fst == NUMBER)
    {
        counter_fst = 0;
        currentmax = maximum;
        cout << "lvl" << level << "\tmax" << currentmax << "\ttrd" << trdnum << endl;
        maximum = -1;
        sem_post(&sem_bar);
        log << "barrier pass" << endl;
    }
    sem_post(&sem_count);

    sem_wait(&sem_bar);
    sem_post(&sem_bar);
}

void ThreadSense::barrier_sec(ofstream& log, int level)
{
    sem_wait(&sem_count);
    counter_sec++;
    if(counter_sec == NUMBER)
    {
        counter_sec = 0;
        sem_post(&sem_bar);
        log << "barrier pass" << endl;
    }
    sem_post(&sem_count);

    sem_wait(&sem_bar);
    sem_post(&sem_bar);
}


void ThreadSense::run(int trdnum, int level, ofstream& log)
{
    int candid = stoi(data[trdnum][level]);
    log << "level:" << level <<" data: " << candid << endl;
    sem_wait(&sem_max);
    if(candid > maximum)
    {
        maximum = candid;
        log << "update maximum" << endl;
    }
    sem_post(&sem_max);
    
    barrier_fst(log, trdnum, level);

    float normalval = candid / (float) currentmax;
    ofstream out;
    string path = string("outputs/") + to_string(trdnum + 1) + ".txt";
    out.open(path, ios_base::app);
    out << normalval << endl;
    out.close();
    
    barrier_sec(log, level);
}

void ThreadSense::operator()(int trdnum)
{
    ofstream log;
    string logPath = string("logs/") + to_string(trdnum + 1) + ".log";
    log.open(logPath, ios_base::out);
    log << "thread " << trdnum << " start" << endl;
    for(int level = 0; level < LEVEL; level++)
    {
        run(trdnum, level, log);
        std::this_thread::sleep_for(std::chrono::seconds(SLP)); 
    }
    log << "thread " << trdnum << " stop" << endl;
    log.close();    
}

void sems_init()
{
    sem_init(&sem_max, 0, 1);
    sem_init(&sem_count, 0, 1);
    sem_init(&sem_bar, 0, 0);
}