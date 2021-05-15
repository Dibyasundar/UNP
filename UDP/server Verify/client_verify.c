#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>

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
    struct sockaddr_in server_address, recv_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);


    char str[100];
    int f=0;
    int len=sizeof(server_address);
    sendto(net_socket, &f,4,0,(struct sockaddr*)&server_address,len);
    while(1)
    {
          recvfrom(net_socket, str, 100, 0, (struct sockaddr *)&recv_address, &len);
          if !memcmp(server_address, recv_address)
          {
            printf("msg from wrog server");
          }
          else
          {
            printf("Time is : %s", str);
          }
    }

    return(0);
}
