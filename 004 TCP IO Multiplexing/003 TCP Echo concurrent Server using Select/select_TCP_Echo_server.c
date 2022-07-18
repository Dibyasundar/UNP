#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/select.h>
#include<string.h>

void print_ip_port(int socket)
{
	struct sockaddr_in ca, sa;
	int len = sizeof(struct sockaddr_in);

	getsockname(socket, (struct sockaddr *) &sa, &len);
	printf("server ip : %s\n", inet_ntoa(sa.sin_addr));
	printf("server port : %d\n", ntohs(sa.sin_port));

	len = sizeof(struct sockaddr_in);
	getpeername(socket, (struct sockaddr *) &ca, &len);
	printf("client ip : %s\n", inet_ntoa(ca.sin_addr));
	printf("clint port : %d\n", ntohs(ca.sin_port));
}
void print_select(fd_set set, int maxfdp)
{
	for(int i =0; i<maxfdp; i++)
	{
		if(FD_ISSET(i, &set))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

int main()
{
	int l_socket  = socket(AF_INET, SOCK_STREAM, 0);
	if(l_socket < 0)
		perror("socket error :");
	else
		printf("socket created .... \n");

	printf("\n+++++++++++++ Before calling the bind function ++++++++\n");
	print_ip_port(l_socket);


	struct sockaddr_in sv_add;
	sv_add.sin_family = AF_INET;
	sv_add.sin_port = htons(33456);
	sv_add.sin_addr.s_addr = inet_addr("0.0.0.0"); // htonl(INADDR_ANY);

	char buffer[200];
	int n;
	int len = sizeof(struct sockaddr_in);
	int br = bind(l_socket, (struct sockaddr *)&sv_add, len);
	if(br<0)
		perror("bind failed : ");
	else
		printf("bind completed .... \n");

	printf("\n+++++++++++++++++++++ after the bind is called +++++++++\n");
	print_ip_port(l_socket);

	int lr = listen(l_socket, 256);
	if(lr < 0)
		perror("listen failed : ");
	else
	{
		printf(" \n ++++++++ started listening with details ++++++++ \n");
		print_ip_port(l_socket);
	}

	int afds[256];
	int i;
	for(i=0; i<256; i++)
		afds[i] = -1;
	fd_set read_set;
	//FD_ZERO(&read_set);
	//FD_SET(l_socket, &read_set);
	int fd, maxfds= l_socket ;
	struct sockaddr_in ca;
	fd_set all_set;
	FD_ZERO(&all_set);
	FD_SET(l_socket, &all_set);
	while(1)
	{
		read_set = all_set;
		printf("before select : ");
		print_select(read_set, maxfds+1);
		printf("After select : ");
		select(maxfds +1 , &read_set, NULL, NULL, NULL);
		print_select(read_set, maxfds+1);
		if(FD_ISSET(l_socket, &read_set))
		{
			len = sizeof(struct sockaddr_in);
			fd = accept(l_socket, (struct sockaddr*)&ca, &len);
			for(i=0;i<256;i++)
			{
				if(afds[i]==-1)
					break;
			}	
			if(i==256)
			{
				printf("Max server capacity reached ...\n");
				continue;
			}
			else
			{
				afds[i] = fd;
				if (maxfds< fd)
				{
					maxfds = fd;
				}
				FD_SET(fd, &all_set);
			}
		}

		for(i=0;i<256;i++)
		{
			if(afds[i] == -1)
				continue;
			else
			{
				if(FD_ISSET(afds[i] ,&read_set))
				{
					n = read(afds[i], buffer, 200);
				       if(n<0)
				       		perror("read_failed");
					else if(n==0)
				 	{
						close(afds[i]);
						FD_CLR(afds[i], &all_set);
						afds[i] =-1;
					}		
				       else
				       {
					       buffer[n] = '\0';
					       write(afds[i], buffer, strlen(buffer));
				       }
				}
			}
		}


	}

}
