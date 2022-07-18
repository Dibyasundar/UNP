#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>

int main(int argc, char *argv[])
{
	fd_set read_set;
	FD_ZERO(&read_set);
	
	struct timeval t;
	t.tv_sec =5;
	
	int net_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(net_socket <0) 
		perror("socket failed : ");
	else
		printf("socket created ... \n");


	struct sockaddr_in serv_addr;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_family = AF_INET;

	int len = sizeof(struct sockaddr_in);
	struct sockaddr_in ca, sa;

	int n;
	char buffer[200];
	while(fgets(buffer, 200, stdin)!=NULL)
	{
		len = sizeof(struct sockaddr_in);
		n =  sendto(net_socket, buffer, strlen(buffer), 0 , (struct sockaddr *)&serv_addr, len);
		if(n<0)
			perror("wriet error :");
		len = sizeof(struct sockaddr_in);
		FD_SET(net_socket, &read_set);
		int sr = select(net_socket+1, &read_set, NULL, NULL, &t);
		if(sr == 0)
		{
		    printf("Time out ... nothing recieved .. exiting ...\n");
		    exit(0);
		}
		else if(sr <0)
		    perror("error in select : ");
		else
		{
		        n = recvfrom(net_socket, buffer, 200, 0, (struct sockaddr *)&serv_addr, &len);
		        if(n<0)
			        perror("read failed :");
		    else
		    {
			    buffer[n] = '\0';
			    printf("server sent : %s \n", buffer);
		    }
	    }
	}
	close(net_socket);
	return(0);

}
