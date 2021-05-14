#include<stdio.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
void handel_alarm (int sig)
{
  printf("Waited for maximum time.... no data recived ... exiting\n");
  exit(0);
}
int main(int argc, char *argv[])
{
    int n;
    char data[201];
    int net_socket;
    net_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    char str[100];
    int f=0;
    int len=sizeof(server_address);
    signal(SIGALRM, handel_alarm);
    sendto(net_socket, &f,4,0,(struct sockaddr*)&server_address,len);
    alarm(5);
    recvfrom(net_socket, str, 100, 0, (struct sockaddr *)&server_address, &len);
    printf("Time is : %s", str);
    return(0);
}
