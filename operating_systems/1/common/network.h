#ifndef NETWORK_H
#define NETWORK_H
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

typedef struct sockaddr_in sockaddr_in_t;

int new_udp_sock();
void initial_address(struct sockaddr_in* address, int port);
void bind_socket(int socket, struct sockaddr_in address);
void initial_server_address(struct sockaddr_in* address, int port);
int new_broadcast_sock();
void broadcast(const char *mess, int sock, int port);

#endif