#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>


#include<signal.h>
void sig_handler(int sig)
{
	printf("Time out ... nothing is recieved ... exit \n");
	exit(0);
}
int main(int argc, char *argv[])
{
	signal(SIGALRM, sig_handler);
	int net_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(net_socket < 0)
		perror("socket failed : ");
	else
		printf("socket created ... \n");

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_port  = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	//inet_aton(argv[1], &serv_addr.sin_addr);
	//inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
	serv_addr.sin_fmaily =  AF_INET;

	int len, l2;

	char buffer[200];
	int n;
	struct sockaddr_in ca;
	struct sockaddr_in send_addr, rec_addr;

	while(fgets(buffer, 200, stdin)!=NULL)
	{
		send_addr = serv_addr;
		len = sizeof(struct sockaddr_in);
		n = sendto(net_socket, buffer, strlen(buffer), 0, (struct sockaddr *)& send_addr, len );
		if(n<0)
			perror("send failed :");
		len = sizeof(struct sockaddr_in);
		getsockname(net_socket, (struct sockaddr *)&ca, &len);
		printf("Local port no : %d\n", ntohs(ca.sin_port));
		l2 = sizeof(struct sockaddr_in);
		alarm(5);
		n = recvfrom(net_socket, buffer, 200, 0, (struct sockaddr *)&rec_addr, &l2);
		if(len != l2 || memcmp(&send_addr, &rec_addr, len) !=0)
		{
			alarm(0);
			printf("recieve from wrong server ... \n");
			continue;
		}
		if(n<0)
			perror("recv failed : ");
		else if(n>0)
		{
			alarm(0);
			buffer[n]='\0';
			printf("recieved from server : %s\n ", buffer);
		}

	}
	close(net_socket);
	return(0);

}
