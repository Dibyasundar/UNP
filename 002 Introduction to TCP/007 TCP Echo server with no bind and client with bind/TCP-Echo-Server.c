#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
void print_sock_details(int net_socket)
{
    int len;
    struct sockaddr_in ca,sa;


    // Getting local details ....
    len = sizeof(struct sockaddr_in);
    getsockname(net_socket, (struct sockaddr *)&ca, &len);
    printf("local ip : %s\n", inet_ntoa(ca.sin_addr));
    printf("local port : %d\n", ntohs(ca.sin_port));

    // Getting remote details ....
    len = sizeof(struct sockaddr_in);
    getpeername(net_socket, (struct sockaddr *)&sa, &len);
    printf("remote ip : %s\n", inet_ntoa(sa.sin_addr));
    printf("remote port : %d\n", ntohs(sa.sin_port));
}
int main(int argc, char *argv[])
{
    int n;
    char data[201];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    printf("socket details before listening ... \n");
    print_sock_details(net_socket);

    listen(net_socket,10);

    printf("Socket details after listeing ... \n");
    print_sock_details(net_socket);

    time_t tick;
    char str[100];
    int fd, len;
    while(1)
    {
        len = sizeof(struct sockaddr_in);
	    fd=accept(net_socket,(struct sockaddr*)&client_address,&len);
	    n = read(fd, str, 100);
        str[n] = '\0';
	    write(fd,str,strlen(str));
    }

    return(0);
}
