#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int n;
    char *send_data, *recv_data;
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));
    send_data = (char *) malloc (200*sizeof(char));
    recv_data = (char *) malloc (200*sizeof(char));

    while (fgets(send_data, 200, stdin) !=NULL)
    {
      write(net_socket,send_data,strlen(send_data));
      recv(net_socket, recv_data,200,0);
      printf("%s",recv_data);
    }
    free(send_data);
    free(recv_data);
    close(net_socket);
    return(0);
}
