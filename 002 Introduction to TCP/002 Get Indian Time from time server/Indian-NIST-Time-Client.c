// Client program to get Indian Time from NIST time server
// Time server url : time-a-g.nist.gov
// Time server ip : 129.6.15.28
// Time server port number : 13
/*
Author 		:	Dibyasundar Das
Course		: 	UNP
Last update	:	18th July 2022
*/

#include<stdio.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h> 
#include<stdlib.h>
int main(int argc, char *argv[])
{
    int n;
    char data[201];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(net_socket<0)
    {
        perror("socket failed :");
    }
    else
    {
        printf("socket created \n");
    }

    // resolve name to ip
    struct hostent *host_entry;
    host_entry = gethostbyname(argv[1]);
    char *ip;
    ip =inet_ntoa(*((struct in_addr *) host_entry->h_addr_list[0]));
    printf("%s\n",ip);


    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(13);
    server_address.sin_addr.s_addr = inet_addr(ip);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));

    n=recv(net_socket, data,200,0);
    printf("%d\n",n);
    printf("%s",data);
    close(net_socket);
    char temp[3];
    temp[3]='\0';
    int hr;
    temp[0]=data[16];
    temp[1]=data[17];
    sscanf(temp,"%d",&hr);

    int min;
    temp[0]=data[19];
    temp[1]=data[20];
    sscanf(temp,"%d",&min);

    hr=hr+5;
    min=min+30;
    if (min>= 60)
    {
	    hr=hr+1;
	    min=min-60;
    }
    if (hr>24)
    {
	    hr=hr-24;
    }
    char *m;
    if (hr>12)
    {
	    m="PM";
	    hr=hr-12;
    }
    if (hr==12)
    {
	    m="PM";
    }
    else
    {
	    m="AM";
    }

    int sec;
    temp[0]=data[22];
    temp[1]=data[23];
    sscanf(temp,"%d",&sec);

    printf("Indian standard time is : %02d:%02d:%02d %s\n",hr,min,sec,m);

    return(0);
}

