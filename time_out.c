#include<stdio.h>

#include<sys/socket.h>

#include<arpa/inet.h>

#include<unistd.h>

int main(int argc, char *argv[])

{	
	//create socket
	int net_socket;
	net_socket = socket(AF_INET, SOCK_STREAM, 0);


	//server address 
	struct sockaddr_in server_address;
    	
	server_address.sin_family = AF_INET;
    	server_address.sin_port = htons(13);
    	server_address.sin_addr.s_addr = inet_addr(argv[1]);

	//connect to server
	connect(net_socket, (struct sockaddr *) &server_address, sizeof( server_address));

	//recv the data
	char data[201];
	int n;
	n = recv(net_socket, data, 200, 0);

	printf("%s",data);

	//close the socket
	close(net_socket);

	return(0);
}



ASSIGNMENT

WRITE a  TCP client program that takes time from time server time-a-g.nist.gov and prints current time in INDIA.
