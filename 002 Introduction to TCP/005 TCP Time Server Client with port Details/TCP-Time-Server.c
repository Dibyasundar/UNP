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
    printf("++++++++++++++++ Inside Server +++++++++++++++++++++\n\n");
    int n;
    char data[201];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    printf("before calling bind function .... \n\n");
    print_sock_details(net_socket);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    printf("\n\n after calling bind function .... \n\n");
    print_sock_details(net_socket);


    listen(net_socket,10);

    printf("\n\n after calling listen function .... \n\n");
    print_sock_details(net_socket);

    time_t tick;
    char str[100];
    int fd;
    int c;
    while(1)
    {
	    fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
        printf("\n\n after calling accept function Detains of new socket .... \n\n");
        print_sock_details(fd);
	    tick=time(NULL);
	    snprintf(str,sizeof(str),"%s",ctime(&tick));
	    printf("%s",str);
	    write(fd,str,strlen(str));
    }

    return(0);
}
