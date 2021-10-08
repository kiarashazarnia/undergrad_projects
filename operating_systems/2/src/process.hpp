#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <vector>
#include <string>

void fork_process(int* fd_pipe, std::string sensor, std::string path);
void write_to_fifo(std::string result);
void share_load(std::vector<std::string>& address, std::string sensor);
int find_major(const std::vector<int>& arr);
std::string judge(const std::string& buffer);
void result_process();
void worker_process(int* fd_pipe);
std::string read_sensor(std::string sensor, std::string path);
void make_fifo();

class Log
{    
    public:
    static bool on;
    static void pl(std::string log);
    static void cl(std::string log);
};

#endif