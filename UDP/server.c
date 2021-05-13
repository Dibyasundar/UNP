#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main(int argc, char *argv[])
{
    int n;
    char data[201];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_DGRAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    time_t tick;
    char str[100];
    int f=0;
    int len=sizeof(client_address);
    while(1)
    {
      recvfrom(net_socket, &f,4,0,(struct sockaddr*)&client_address,&len);
      tick=time(NULL);
	    snprintf(str,sizeof(str),"%s",ctime(&tick));
      sendto(net_socket, str, strlen(str), 0, (struct sockaddr *)&client_address, len);
    }
    close(net_socket);
    return(0);
}
