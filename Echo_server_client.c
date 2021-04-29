/////////Design a echo server and client 

/////////////  Server.c ///////////////////////////////////////
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
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //construct a server
    //where we want to Listen to
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    listen(net_socket,10);

    int fd;
    int c;

    while(1)
    {
	    fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
	    printf("Accepted\n");
      n=recv(fd, data,200,0);
	    write(fd,data,strlen(data));
    }

    return(0);
}



/////////////////////////////////// client.c 

#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int n;
    char *data;
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
    data = (char *) malloc (200*sizeof(char));
    while (fgets(data, 200, stdin) !=NULL)
    {
      write(net_socket,data,strlen(data));
      n=recv(net_socket, data,200,0);
      printf("%s",data);
      free(data);
      fflush(stdin);
      data = (char *) malloc (200*sizeof(char));
    }
    close(net_socket);
    return(0);
}

