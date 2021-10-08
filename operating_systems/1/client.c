#include "common/common.h"
#include "common/network.h"
#include "common/user.h"
#include "common/chat.h"
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h> 

int main(int argc, char** argv) 
{
    chat_state_t chat_state = Off;
    int chat_port;
    if(argc != 3)
    {
        error_log(MSG_INVALID_INPUT);
    }
    state_t state = Off;
    int server_port = atoi(argv[1]);
    int client_port = atoi(argv[2]);
    int maxfds, select_status;
    int broadcast_reciever_fd, command_fd;
    int n;
    socklen_t len;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    char buffer[MAXLINE]; 
    fd_set read_fds;
    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_ZERO(&read_fds);
    struct sockaddr_in server_address, client_address;
    initial_server_address(&server_address, server_port);
    initial_address(&client_address, client_port);
    command_fd = new_udp_sock();
    bind_socket(command_fd, client_address);
    broadcast_reciever_fd = new_broadcast_sock();
    struct sockaddr_in broadcast_address;
    initial_address(&broadcast_address, BPORT);
    bind_socket(broadcast_reciever_fd, broadcast_address);
    maxfds = max(broadcast_reciever_fd, command_fd) + 1;

    while(true)
    {
        FD_SET(stdinfd, &read_fds);
        FD_SET(broadcast_reciever_fd, &read_fds);
        FD_SET(command_fd, &read_fds);

       	select_status = select(maxfds, &read_fds, &write_fds, NULL, &tv); 
        if(select_status < 0)
            error_log("select");
            
		if(FD_ISSET(broadcast_reciever_fd, &read_fds))
		{
            len = sizeof(broadcast_address);
            bzero(buffer, sizeof(buffer));
			n = recvfrom(broadcast_reciever_fd, (char*)buffer, MAXLINE, 0, 
                (struct sockaddr*)&broadcast_address, &len);
            if(n < 0)
                error_log("recieve");
            printstr(stdoutfd, "(BROADCAST)\n");
            println(buffer);
        }

        if(FD_ISSET(stdinfd, &read_fds))
		{ 
            bzero(buffer, sizeof(buffer));
            read(stdinfd, buffer, sizeof(buffer));
            if(chat_state == Off)
            {
                chat_port = parse_connect_command(buffer);
                if(chat_port)
                {
                    chat_state = Master;
                    server_address.sin_port = chat_port;
                    bzero(buffer, MAXLINE);
                    strcpy(buffer, CONNECT);
                    strcat(buffer, SPACE);
                    strcat(buffer, itos(client_address.sin_port));
                    strcat(buffer, SPACE);
                }
            }
            n = sendto(command_fd, (const char*)buffer, sizeof(buffer), 0, 
                (struct sockaddr*)&server_address, sizeof(server_address));
            if(equals(buffer, DISCONNECTN))
            {
                chat_state = Off;
                server_address.sin_port = htons(server_port);
            }
            if(n < 0)
                error_log("send"); 
        }

        if(FD_ISSET(command_fd, &read_fds))
		{
            bzero(buffer, sizeof(buffer));
            read(command_fd, buffer, sizeof(buffer));
            println(buffer);
            if(chat_state == Off)
            {
                chat_port = parse_connect_command(buffer);
                if(chat_port)
                {
                    chat_state = Slave;
                    server_address.sin_port = chat_port;
                    printstr(stdoutfd, MSG_CONNECTED_TO);
                    println(itos(chat_port));
                }
            }
            if(equals(buffer, DISCONNECTN))
            {
                chat_state = Off;
                server_address.sin_port = htons(server_port);
            }
        }
    }
    return 0;
}