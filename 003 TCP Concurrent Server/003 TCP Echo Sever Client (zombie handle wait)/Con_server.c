#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
// pid_t wait(int *sat_loc);
//#include<time.h>
//#include<string.h>
void do_nothing(int sig)
{
	pid_t child_id;
	child_id = wait(NULL);
	printf("The child terminated is : %ld\n", child_id);
}
int main(int argc, char *argv[])
{
	signal(SIGCHLD, do_nothing);
	// listening socket
	int l_socket;
	l_socket = socket(AF_INET, SOCK_STREAM, 0);

	// store server details
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY) ;//inet_addr(argv[1])i;
	// srever_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// inet_aton(char *, struct in_adrr *)
	// inet_aton("127.0.0.1", &server_addr.sin_addr);
	// char * inet_ntoa(struct in_addr );
	// char ip[30] = net_ntoa(server_addr.sin_addr);
	int len = sizeof(struct sockaddr_in);
	//bind the socket to port
	bind( l_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
	getsockname(l_socket, (struct sockaddr *)&server_addr, &len);
	printf("Port number is : %d\n", (int)ntohs(server_addr.sin_port));
	// start listen process
	listen(l_socket, 10);

	int s_socket;
	struct sockaddr_in client_addr;
	int client_sz= sizeof(struct sockaddr);
	char data[200];
	int n;
	//time_t tick;
	while(1)
	{
		// accept + (read/ write) + close_new_socket
		s_socket = accept( l_socket, (struct sockaddr *) &client_addr, &client_sz);
		if ( fork()==0)
		{
			///
			close(l_socket);
			while(1)
	                {
        	                n = recv(s_socket, data, 199, 0);
                	        if(n == 0)
                        	        break;
                        	data[n] = '\0';
                        	write(s_socket, data, sizeof(data));
                	}
			getpeername(s_socket, (struct sockaddr *) &client_addr, &client_sz);
			printf("%s is the ip exiting... \n", inet_ntoa(client_addr.sin_addr));
			printf("%d is the port of client \n", ntohs(client_addr.sin_port));
			// sockaddr_in -> sin_family
			// sockaddr_in -> sin_port
			// sockaddr_in -> sin_addr -> s_addr
                	close(s_socket);
			exit(0);
		}
		else
		{
			close(s_socket);
		}
	}
	return(0);
}
