#include "network.h"
#include "common.h"
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

void bind_socket(int socket, struct sockaddr_in my_address)
{
	int binded = bind(socket, (struct sockaddr*)&my_address, sizeof(my_address));
    if(binded < 0)
        error_log("bind server udp");
}

void initial_address(struct sockaddr_in* address, int port)
{
    bzero(address, sizeof(struct sockaddr_in)); 
	address -> sin_family = AF_INET; 
	address -> sin_addr.s_addr = htonl(INADDR_ANY); 
	address -> sin_port = htons(port);
}

void initial_server_address(struct sockaddr_in* server, int port)
{ 
    bzero(server, sizeof(struct sockaddr_in));     
    server -> sin_family = AF_INET; 
    server -> sin_port = htons(port); 
    server -> sin_addr.s_addr = inet_addr(LH);
}

int new_broadcast_sock()
{
    int bsock = new_udp_sock();
	int enable = 1;
    if( setsockopt(bsock, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable))<0 ||    
        setsockopt(bsock, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable))<0 ||    
	    setsockopt(bsock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable))<0)
		error_log("setsockopt broadcast");
    return bsock;
}

void broadcast(const char *mess, int bsock, int port)
{
    struct sockaddr_in server;
    if(bsock < 0)
        return;

    bzero(&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(BPORT);//(port);
    server.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    int res = sendto(bsock, mess, strlen(mess), 0, 
        (struct sockaddr *)&server, sizeof(struct sockaddr_in));
    if(res < 0)
        error_log("sendto");
    server_log(MSG_BROADCASTING);
    server_log(mess);
}

int new_udp_sock()
{
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
        error_log("udp socket");
    return sock_fd;
}
