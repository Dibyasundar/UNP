#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>


#include<time.h>
#include<string.h>

#include<signal.h>

int net_socket;

void handle_sigint(int sig)
{
  close(net_socket);
  fflush(stdout);
  fflush(stdin);
  exit(0);
}

int main(int argc, char *argv[])
{
    int n;
    char *data;
    //create a socket

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
    pid_t pid;
    fflush(stdout);
    fflush(stdin);

    signal(SIGINT, handle_sigint);
    printf("Parent PID=%ld\n",(long)getpid());//ID of Parent
    while(1)
    {
        fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
        data = (char *) malloc (200*sizeof(char));
        if ((pid = fork())==0)
        {
        	  close(net_socket);
        	  printf("Child PID=%ld\n",(long)getpid());//ID of Child
            //ps aux | grep Z to see if the clid became a zombie
        	  while(1)
        	  {
        	    	  sleep(2);
        		  n=recv(fd, data,200,0);
        		  if(n==0)
        		    break;
        		  write(fd,data,strlen(data));
        	  }
        	  close(fd);
            break;
        }
        else
        {
              signal(SIGCHLD, SIG_IGN);
	           close(fd);
        }
        free(data);
  }
  close(net_socket);
  fflush(stdout);
  fflush(stdin);
  return(0);
}
