#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
	int net_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int val =1, val_len = sizeof(int);
	setsockopt(net_socket, SOL_SOCKET, SO_BROADCAST, &val, val_len);

	struct sockaddr_in own_addr;
	own_addr.sin_family = AF_INET;
	own_addr.sin_port = htons(33456);
	own_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(net_socket, (struct sockaddr *)&own_addr, sizeof(struct sockaddr_in));

	struct sockaddr_in server_addr;
	int len = sizeof(struct sockaddr_in);
	char buffer[20];

	int n = recvfrom(net_socket, buffer, 20, 0, (struct sockaddr *)&server_addr, &len);

	buffer[n] = '\0';
	printf("Server sent : %s\n", buffer);

	close(net_socket);
	return(0);

}
