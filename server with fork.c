################################ server prog ###############3

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
    pid_t pid;
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    listen(net_socket,10);
    time_t tick;
    char str[100];
    int fd;
    int c;
    while(1)
    {
	    fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
	    printf("Accepted");
      if ((pid = fork())==0)
      {
        close(net_socket);
        while(1)
        {
          tick=time(NULL);
          snprintf(str,sizeof(str),"%s",ctime(&tick));
          write(fd,str,strlen(str));
        }
      }
      else
      {
        close(fd);
      }
    }

    return(0);
}





########################### client.c #################################


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
    server_address.sin_port = htons(4600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));
    while(1)
    {
      n=recv(net_socket, data,200,0);
      printf("%d\n",n);
      printf("%s",data);
    }
    close(net_socket);
    return(0);
}
