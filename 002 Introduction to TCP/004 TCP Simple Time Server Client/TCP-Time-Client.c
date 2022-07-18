// Client program Time server client application
/*
Author 		:	Dibyasundar Das
Course		: 	UNP
Last update	:	18th July 2022
*/
#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    int n;
    char data[201];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));

    n=recv(net_socket, data,200,0);
    printf("%d\n",n);
    printf("%s",data);
    close(net_socket);
    return(0);
}
