#include <cstdlib>
#include <cstdio> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
#include "process.hpp"
#include "values.hpp"
#include "probe.hpp"

using namespace std;

int main()
{
    int sensor;
    pid_t res_stat = 0;
    int status;
    string s_sensor;
    cout << WELLCOME << endl;
    cout << "logging?";
    cin >> Log::on;
    vector<string> address = probe(PATH);
    Log::pl("database is probed");
    pid_t pid_result;
    make_fifo();
    cout << MSG_ASK;
    while(cin >> sensor)
    {
        pid_result = fork();
        if (pid_result < 0) 
        { 
            perror("fork failure");
		    exit(1); 
        }
        else if(pid_result == 0)
        {
            result_process();
        }
        else if (pid_result > 0) 
        {
            s_sensor = to_string(sensor);
            share_load(address, s_sensor);
            while(res_stat == 0)
                res_stat = waitpid(pid_result, &status, WNOHANG);
            if (res_stat == -1) {
                cout << MSG_ERR << endl;
            } else {
                cout << MSG_ASK << endl;
            }
        }    
    }
    return 0;
}