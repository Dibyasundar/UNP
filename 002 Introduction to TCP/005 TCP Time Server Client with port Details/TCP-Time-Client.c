#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
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
    printf("+++++++++++++++++++ In client ++++++++++++++++++\n\n");
    int n;
    char data[201];
    //create a socket
    int net_socket, len;

    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("\n\nSocket details before calling connect ....\n");
    print_sock_details(net_socket);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));

    printf("\n\nSocket details aftercd .. calling connect ....\n");
    print_sock_details(net_socket);

    printf("\n\n Time recieved : ");
    n=recv(net_socket, data,200,0);
    data[n] = '\0';
    printf("%s\n",data);
    close(net_socket);
    return(0);
}
