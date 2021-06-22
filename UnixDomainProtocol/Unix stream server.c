#include<stdio.h>
#include<sys/socket.h>
#include <sys/un.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
int sockfd;

void handle_int(int sig)
{
	close(sockfd);
	printf("Exiting Safely....\n");
	exit(0);
}

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
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	unlink(argv[1]);
	
	bzero(&addr1, sizeof(addr1));
	
	addr1.sun_family = AF_LOCAL;
	strcpy(addr1.sun_path, argv[1]);
	bind(sockfd, (struct sockaddr *) &addr1, strlen(addr1.sun_path) +sizeof (addr1.sun_family));
	
	listen(sockfd, 10);
	
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, handle_int);
	
	while(1) 
	{
		clilen = sizeof(addr2);
		if ( (connfd = accept(sockfd, (struct sockaddr *) &addr2, &clilen)) < 0) 
		{
 			if (errno == EINTR)
				continue;
 			else
 				printf("error");
 		}
 		if ( (childpid = fork()) == 0) 
 		{
			close(sockfd); 
			while(recv(connfd, data,200,0) != 0)
			{
          			write(connfd,data,strlen(data));
          		}
			exit(0);
 		}
 		else
 		{
 			close(connfd);
 		}
 	}
	return(0);	
}
