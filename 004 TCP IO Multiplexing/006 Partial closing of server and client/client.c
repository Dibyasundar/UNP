#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/select.h>
// signal(signal_id, function_name)
int net_socket;
void int_handel(int sig)
{
	printf("\n Exit from client .....\n");
	close(net_socket);
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, int_handel);
	// create socket
	net_socket = socket (AF_INET, SOCK_STREAM, 0);
	
	// connect to server
	// define address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	// call connect function
	connect(net_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	//
	//recv data
	FILE *fp = fopen("file.txt","r");
	int fd = fileno(fp);
	fd_set rset;
	FD_ZERO(&rset);
	int maxfd;
	char data[201];
	int n;
	int flag =0;
	while(1)
	{
		if(flag == 0)
		{
			FD_SET(fd, &rset);
		}
                FD_SET(net_socket , &rset);
		if(flag==0)
			maxfd = (fd > net_socket ? fd : net_socket) + 1;
		else
			maxfd =  net_socket + 1;
		select(maxfd, &rset, NULL, NULL, NULL);
		if (FD_ISSET(net_socket,  &rset))
		{
			n= recv(net_socket, data,200, 0);
			if(n==0)
			{
				printf("Server terminated the connection ...\n");
				break;
			}
			else
			{
				data[n]  = '\0';
				printf("%s\n",data);
			}
		}
		if(FD_ISSET(fd, &rset))
		{
			if(fgets(data, 200, fp) == NULL)
			{
				printf("All data has been read");
				close(fd);
				flag = 1;
				FD_CLR(fd, &rset);
				shutdown(net_socket, SHUT_WR);
			}
			else
			{
				write(net_socket, data, strlen(data));
			}
		}
	}
	//close the connection
	shutdown(net_socket, SHUT_RD);
	return(0);
}
