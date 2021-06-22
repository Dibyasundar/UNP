#include<stdio.h>
#include<sys/socket.h>
#include <sys/un.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int connfd, clilen;
	pid_t childpid;
	char data[201];
	struct sockaddr_un addr1, addr2;
	if (argc != 2)
		{
			printf("Enter path name");
			exit(0);
		}
	connfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	unlink(argv[1]);
	
	bzero(&addr1, sizeof(addr1));
	
	addr1.sun_family = AF_LOCAL;
	strcpy(addr1.sun_path, argv[1]);
	bind(connfd, (struct sockaddr *) &addr1, sizeof (addr1));
	
	clilen=sizeof(addr2);
	while(1)
	{
		recvfrom(connfd, data,200,0,(struct sockaddr*)&addr2,&clilen);
      		sendto(connfd, data, strlen(data), 0, (struct sockaddr *)&addr2, clilen);
	}

	return(0);	
}
