#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <time.h>
#include "common/common.h"
#include "common/utility.h"
#include "common/network.h"
#include "common/values.h"
#include "common/competition.h"

int main(int argc, char** argv) 
{
	competition_state_t competition_state = Wait;
	int qindex = 0;
	int asking = true;
	if(argc != 2)
	{
		error_log(MSG_INVALID_INPUT);
	}
	int port = atoi(argv[1]);
    int broadcast_fd, command_fd;
    char* response; 
	sockaddr_in_t server_address, client_address;
	initial_address(&server_address, port);
	int select_status, maxfds;
    fd_set read_fds, write_fds;
	char buffer[MAXLINE]; 
	struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
	ssize_t n;
	socklen_t len;
	broadcast_fd = new_broadcast_sock();
	command_fd = new_udp_sock();
	bind_socket(command_fd, server_address);
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	maxfds = max(command_fd, broadcast_fd) + 1; 

	time_t clock = time(NULL);
	
	while(true)
    { 
        FD_SET(command_fd, &read_fds);
        FD_SET(broadcast_fd, &write_fds); 

		select_status = select(maxfds, &read_fds, &write_fds, NULL, &tv); 
        if(select_status < 0)
            error_log("select");

		if (FD_ISSET(command_fd, &read_fds))
		{
			len = sizeof(client_address);
			bzero(buffer, sizeof(buffer)); 
			n = recvfrom(command_fd, buffer, MAXLINE, 0, (sockaddr_in_t*)&client_address, &len);
			response = service(client_address, buffer, qindex, competition_state);
			server_log_response(response);
			sendto(command_fd, (const char*)response, MAXLINE, 0, 
				(sockaddr_in_t*)&client_address, sizeof(client_address));
		}

		if (FD_ISSET(broadcast_fd, &write_fds))
		{
			switch(competition_state)
			{
				case Wait:
					if((time(NULL) - clock) > COMPETITION_INTERVAL)
					{
						competition_state = Inform;
						broadcast(MSG_INFORM_COMPETE, broadcast_fd, BPORT);
						clock = time(NULL);
					}
				break;
				case Inform:
					if((time(NULL) - clock) > REGISTER_DELAY)
					{	
						competition_state = Lock;
						broadcast(MSG_WARN_COMPETE, broadcast_fd, BPORT);
						clock = time(NULL);
					}
				break;
				case Lock:
					if((time(NULL) - clock) > DELAY)
					{	
						broadcast(MSG_START_COMPETE, broadcast_fd, BPORT);
						competition_state = Run;
					}
				break;
				case Run:
					if((time(NULL) - clock) > SEC10 && asking)
					{	
						if(qindex == QUESTIONS)
						{
							qindex = 0;
							finish_competition();
							broadcast(MSG_END_COMPETE, broadcast_fd, BPORT);
							broadcast(report_massage(), broadcast_fd, BPORT);
							competition_state = Wait;
						} else
						{
							broadcast(question[qindex], broadcast_fd, BPORT);
							qindex++;
						}
						clock = time(NULL);
						asking = false;
					}
					else if(time(NULL) - clock > SEC10 && !asking)
					{
						bzero(buffer, MAXLINE);
						strcpy(buffer, MSG_CORRECT_ANSWER);
						strcat(buffer, itos(answer[qindex-1]+1));
						broadcast(buffer, broadcast_fd, BPORT);
						clock = time(NULL);
						asking = true;
					}
				break;
			}
		} 
	} 
}