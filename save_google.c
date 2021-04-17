#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>

#include <netdb.h>

#include<stdlib.h>
#include<string.h>

#include <locale.h>

int main(int argc, char *argv[])
{

    int n;
    char data[201];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);


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
    server_address.sin_port = htons(443);
    server_address.sin_addr.s_addr = inet_addr(ip);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));

    char *sendline="GET / HTTP/1.1\r\nConnection: close\r\n\r\n";
    write(net_socket, sendline, strlen(sendline));

    setlocale(LC_ALL, "en_US.UTF-8");
    FILE *fp;
    fp = fopen("google.html", "w");
    n=recv(net_socket, data,200,0);
    while(n!=0)
    {
    	printf("%s",data);
	fputs(data, fp);
	n=recv(net_socket,data,200,0);
    }
    fclose(fp);
    close(net_socket);
    

    return(0);
}

