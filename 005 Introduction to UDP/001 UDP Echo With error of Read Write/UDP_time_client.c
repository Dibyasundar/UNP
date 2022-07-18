#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int u_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(u_socket <0)
		perror("socket failed : ");
	else
		printf("socket created .... \n");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	int len;
	len = sizeof(struct sockaddr_in);
	int cr = connect(u_socket, (struct sockaddr*)&serv_addr, len);
	if (cr<0)
		perror("connect failed :");
	int n;
	char buffer[200];
	printf("Press 1 :to get time \n pess CTRL+D : to exit\n enter ur choice : ");
	while(fgets(buffer, 200, stdin)!=NULL)
	{
	    if(strcmp(buffer, "1\n")==0)
	    {
		    n = write(u_socket, buffer, strlen(buffer));
		    if(n<0)
			    perror("write error : ");
		    n = read(u_socket, buffer, 200);
		    if(n<0)
			    perror("read filed ....\n");
		    buffer[n] = '\0';
		    printf("Current time : %s\n", buffer);
		    }
		    else
		    {
		        printf("Wrong choice ... \n");
		     }
		        printf("Press 1 :to get time \n pess CTRL+D : to exit\n enter ur choice : ");
	}
	close(u_socket);
	return(0);
}
