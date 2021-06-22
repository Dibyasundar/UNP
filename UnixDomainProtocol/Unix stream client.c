#include<stdio.h>
#include<sys/socket.h>
#include <sys/un.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>
#include<signal.h>

int main(int argc, char *argv[])
{
	int sockfd;
	char data[201];
	struct sockaddr_un addr1;
	if (argc != 2)
		{
			printf("Enter path name");
			exit(0);
		}
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	
	bzero(&addr1, sizeof(addr1));
	
	addr1.sun_family = AF_LOCAL;
	strcpy(addr1.sun_path, argv[1]);
	connect(sockfd, (struct sockaddr *) &addr1, sizeof(addr1));
	while (fgets(data, 200, stdin) !=NULL)
	 {
	      write(sockfd,data,strlen(data));
	      recv(sockfd, data,200,0);
	      printf("%s",data);
	 }
	
	return(0);	
}
