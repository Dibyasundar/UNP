#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
// SIGALRM : signal for time out
// alarm( time in sec );
// signal (SIGALRM, sig_handel);
void sig_handel(int sig)
{
	printf("Time out has occured ... Nothing is recieved ...\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGALRM, sig_handel);
	
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
	{;
		len = sizeof(struct sockaddr_in);
		n =  sendto(net_socket, buffer, strlen(buffer), 0 , (struct sockaddr *)&serv_addr, len);
		if(n<0)
			perror("wriet error :");
		len = sizeof(struct sockaddr_in);
		alarm(5);
		n = recvfrom(net_socket, buffer, 200, 0, (struct sockaddr *)&serv_addr, &len);
		if(n<0)
			perror("read failed :");
		else
		{
			buffer[n] = '\0';
			printf("server sent : %s \n", buffer);
		}
	}
	close(net_socket);
	return(0);

}
