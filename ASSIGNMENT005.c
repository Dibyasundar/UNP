//Write a program where the hosts 1 accepts a string of two numbers 
//sent by host 2 and host 1 replies with the sum of two number. 

//::::::::::::::::::::::::::::::::::::::::::::::::::::::Server Code::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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
    char *data;
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    listen(net_socket,10);

    //processing the string to sum the number
    char str[100];
    int fd;
    int c,i,k;
    char num1[10], num2[10];
    int location_space;
    while(1)
    {
	    fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
      data = (char *) malloc(200*sizeof(char));
	    n=recv(fd, data,200,0);
      k=0;
	    for(i=0;i<strlen(data);i++)
	    {
		    if(data[i]==' ')
		    {
          num1[k]='\0';
			    location_space=i;
          break;
		    }
        else
        {
          num1[k]=data[i];
          k=k+1;
        }
	    }
      k=0;
      for(i=location_space+1;i<strlen(data);i++)
      {
        num2[k]=data[i];
        k=k+1;
      }
      num2[k]='\0';
      sprintf(str, "Sum of %d and %d is %d", atoi(num1), atoi(num2) atoi(num1)+atoi(num2));

      //sending the data to client_address
	    write(fd,str,strlen(str));
      close(fd);
      free(data);
    }

    return(0);
}


  
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::Cient Code::::::::::::::::::::::::::::::::::::::::::::::::::::::::  

#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[])
{
    fflush(stdin);
    int n;
    char data[201];
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
    char *str;
    str = (char*) malloc((strlen(argv[2])+strlen(argv[3])+1)*sizeof(char));
    sprintf(str, "%s %s", argv[2],argv[3]);
    write(net_socket,str,strlen(str));
    n=recv(net_socket, data,200,0);
    printf("%s\n",data);
    close(net_socket);
    return(0);
}




//The problem is to implement a client - server user-level application using sockets API in C. 
//The Server application has to support at least five clients simultaneously. Server accepts strings 
//from clients (even multiple strings from each client) and replies with reverse strings. For example, 
//when client sends “IITHYD”, Server replies with “DYHTII”. Both server and client(s) have to output both 
//sending & receiving strings on the terminal. 
