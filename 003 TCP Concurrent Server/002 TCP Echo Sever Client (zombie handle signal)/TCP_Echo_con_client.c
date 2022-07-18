#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "unistd.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    int n;
    int net_socket;
    net_socket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5900);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect(net_socket, (struct sockaddr *) &server_address,sizeof(server_address));
    char msg[200];
    char data[200];
    while(1)
    {
        scanf("%s",msg);
        write(net_socket,msg, strlen(msg));
        recv(net_socket,data,199,0);
        printf("recieved from server : %s",data);

    }

}