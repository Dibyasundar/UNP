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
	
	bzero(&addr1, sizeof(addr1));
	
	addr1.sun_family = AF_LOCAL;
	strcpy(addr1.sun_path, tmpnam(NULL));
	
	bind(connfd, (struct sockaddr *) &addr1, sizeof (addr1));
	
	
	bzero(&addr2, sizeof(addr2));
	
	addr2.sun_family = AF_LOCAL;
	strcpy(addr2.sun_path, argv[1]);
	
	clilen=sizeof(addr2);
	while(1)
	{
		fgets(data, 200, stdin);
	    	sendto(connfd, data, 200,0,(struct sockaddr*)&addr2,clilen);
	    	recvfrom(connfd, data, 200, 0, (struct sockaddr *)&addr2, &clilen);
	    	printf("server sent : %s", data);
	}

	return(0);	
}
