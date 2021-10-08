#include "process.hpp"
#include "values.hpp"
#include <cstdlib>
#include <cstdio> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>

using namespace std;



void share_load(vector<string>& address, string sensor)
{
    int* pipes = new int[2 * address.size() * sizeof(int)];
    int pipe_index = 0;
    for(string path: address)
    {
		Log::pl(to_string(pipe_index) + " fork");
        fork_process(pipes + pipe_index * 2, sensor, address[pipe_index]);
        pipe_index += 1;
    }
}

void fork_process(int* fd_pipe, string sensor, string path)
{
    pid_t pid;
	string buffer;
	if (pipe(fd_pipe) < 0) 
	{ 
		perror("pipe failure"); 
		exit(1);
	}
	pid = fork(); 

	if (pid < 0) 
	{ 
		perror("fork failure" );
		exit(1);
	} 

	else if (pid > 0) 
	{ 
		buffer = string(path);
		buffer.append(DELIM);
		buffer.append(sensor);
		close(fd_pipe[0]);
		write(fd_pipe[1], buffer.c_str(), buffer.size() + 1);
		close(fd_pipe[1]);
	}
	else if(pid == 0)
	{ 
        worker_process(fd_pipe);
	}
}

void make_fifo()
{
	remove(FIFO_PATH);
	if(mkfifo(FIFO_PATH, FIFO_WRITE) < 0)
	{
		perror("fifo make");
	}
	else
	{
		Log::cl("fifo made");
	}
}
void worker_process(int* fd_pipe)
{
	char* input[LEN];
	close(fd_pipe[1]);
	read(fd_pipe[0], input, LEN); 
	string buffer = string((const char*) input);
	int delim = buffer.find(DELIM);
	string path = buffer.substr(0, delim);
	string sensor = buffer.substr(delim + 1, buffer.size());
	string result = read_sensor(sensor, path);
	write_to_fifo(result);
	close(fd_pipe[0]); 
	Log::cl(string("exit by result ") + result);
	exit(0);
}

void write_to_fifo(string result)
{
	result.append(DELIM);
	fstream fifo;
	Log::cl("opening fifo");
	fifo.open(FIFO_PATH, fstream::app);
	fifo.write(result.c_str(), result.size());
	fifo.close();
}

string read_sensor(string sensor, string path)
{
	Log::cl(string("sensor:") + sensor + string(" in path:") + path);
    ifstream file;
    string line;
    string number;
    string value;
    int sp;
    file.open(path.c_str());
	if(!file.good())
	{
		perror("file");
		exit(1);
	}
    while (getline(file, line))
    {
		sp = line.find(SPACE);
        number = line.substr(0, sp);
        if(number.compare(sensor) == 0) 
        {
            value = line.substr(sp + 1, line.size());
            break;
        }
    }
    file.close();
    return value;
}

void result_process()
{
	Log::cl("result process");
	char buffer[LEN];
	string results;
	string line;
	int fd = open(FIFO_PATH, O_RDONLY);
	int more;
	int finish;
	while(true)
	{
		more = read(fd, buffer, LEN);
		if(more > 0)
		{
			finish = 0;
			results.append(buffer);
		}
		else
		{
			finish++;
		}
		if(finish > TIME)
		{
			Log::cl(string("fifo:") + results);
			line = judge(results);
			cout << "result: " << line << endl;
			results.clear();
			break;
		}
	}
	close(fd);
	flush(cout);
	flush(cerr);
	exit(0);
}

string judge(const string& res)
{
	vector<int> values;
	string val_s;
	int result;
	int delim = 0;
	int pos = 0;
	int val;
	while(delim != string::npos && pos < res.size())
	{
		delim = res.find(DELIM, pos);
		try
		{
			val_s = res.substr(pos, delim - pos);
			val = stoi(val_s);
			values.push_back(val);
		}
		catch (const std::exception& e) {Log::cl(string("NaN") + val_s);}
		pos = delim + 1;
	}
	result = find_major(values);
	return to_string(values[result]);
}

int find_major(const vector<int>& arr) 
{ 
	int n = arr.size();
	Log::cl(string("results number: ") + to_string(n));
	if(n == 0)
	{
		cout << "no data" << endl;
		exit(0);
	}
    int maxCount = 0;  
    int index = -1;
    for(int i = 0; i < n; i++) 
    { 
        int count = 0; 
        for(int j = 0; j < n; j++) 
        { 
           if(arr[i] == arr[j]) 
            count++; 
        } 
        if(count > maxCount) 
        { 
            maxCount = count; 
            index = i; 
        } 
    }
    return index;
} 

bool Log::on = false;

void Log::pl(std::string log)
{
	if(Log::on) std::cerr << "p  " << log << std::endl;
}

 void Log::cl(std::string log)
{
	if(Log::on) std::cerr << "c  " << log << std::endl;
}