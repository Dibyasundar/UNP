// Client program to NIST time server
// Time server url : 
// Time server ip : 
// Time server port number : 13
/*
Author 		:	Dibyasundar Das
Course		: 	UNP
Last update	:	9th July 2022
*/

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[])
{	
	//create socket
	int net_socket;
	net_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(net_socket < 0)
	{
		perror("Socket creation failed : ");
	}
	else
	{
		printf("socket created...\n");
	}

	//server address 
	struct sockaddr_in server_address;
    	
	server_address.sin_family = AF_INET;
    server_address.sin_port = htons(13);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

	//connect to server
	int cr = connect(net_socket, (struct sockaddr *) &server_address, sizeof( server_address));
	if(cr <0)
	{
		perror("connect error :");
	}

	//recv the data
	char data[201];
	int n;
	n = recv(net_socket, data, 200, 0);

	printf("%s",data);

	//close the socket
	close(net_socket);

	return(0);
}