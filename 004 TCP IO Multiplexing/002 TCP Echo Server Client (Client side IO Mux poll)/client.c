#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<poll.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int net_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(net_socket <0)
		perror("socket failed .... : ");
	else
		printf("socket completed  ...\n");

	struct sockaddr_in s_addr, sa, ca;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(argv[2]));
	s_addr.sin_addr.s_addr = inet_addr(argv[1]);
	// inet_aton(argv[1], &s_addr.sin_addr);
	// inet_pton(AF_INET, argv[1], &s_addr.sin_addr);
	
	int len = sizeof(struct sockaddr_in);
	int cr = connect(net_socket, (struct sockaddr *) &s_addr, len);
	if(cr<0)
		perror("connect failed .... : ");
	else
	{
		printf("connect completed ... \n");
		len = sizeof(struct sockaddr_in);
		getsockname(net_socket, (struct sockaddr *) &ca, &len);
		printf("client ip :  %s\n", inet_ntoa(ca.sin_addr));
		printf("client port : %d\n", ntohs(ca.sin_port));

		len = sizeof(struct sockaddr_in);
		getpeername(net_socket, (struct sockaddr *) &sa, &len);
		printf("server ip : %s\n", inet_ntoa(sa.sin_addr));
		printf("server port : %d\n", ntohs(sa.sin_port));
	}

	char buffer[200];
	int n;
	struct pollfd fds[2];
	while(1)
	{
		fds[0].fd = fileno(stdin);
		fds[0].events = POLLRDNORM;
		fds[1].fd = net_socket;
		fds[1].events = POLLRDNORM;
		poll(fds, 2, -1);

		if(fds[0].revents & POLLRDNORM)
		{
			if(fgets(buffer, 200, stdin)==NULL)
                	{
                        	printf("User finsished ..\n");
                        	exit(0);
                	}
                	write(net_socket, buffer, strlen(buffer));
		}
		if(fds[1].revents & POLLRDNORM)
		{
			n = read(net_socket, buffer, 200);
			if(n==0)
			{
				printf("FIN has been recieved \n");
				exit(0)
			}
			buffer[n]='\0';
			printf("Recieved from server : %s\n", buffer);

		}
	}

return(0);
}
