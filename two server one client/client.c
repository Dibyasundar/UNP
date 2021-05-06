#include<stdio.h>

#include<sys/socket.h>

#include<arpa/inet.h>

#include<unistd.h>

#include<stdlib.h>

#include<string.h>

#include<sys/select.h>



int main(int argc, char *argv[])

{

    int n;

    char *send_data, *recv_data1, *recv_data2, *ch;

    //create a socket

    int net_socket1, net_socket2;
    net_socket1 = socket(AF_INET, SOCK_STREAM, 0);
    net_socket2 = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server

    //where we want to connect to

    struct sockaddr_in server1_address;
    server1_address.sin_family = AF_INET;
    server1_address.sin_port = htons(5600);
    server1_address.sin_addr.s_addr = inet_addr(argv[1]);
    connect(net_socket1, (struct sockaddr *)&server1_address, sizeof(server1_address));



    struct sockaddr_in server2_address;
    server2_address.sin_family = AF_INET;
    server2_address.sin_port = htons(2000);
    server2_address.sin_addr.s_addr = inet_addr(argv[1]);
    connect(net_socket2, (struct sockaddr *)&server2_address, sizeof(server2_address));



    recv_data1 = (char *) malloc (200*sizeof(char));

    recv_data2 = (char *) malloc (200*sizeof(char));

    send_data = (char *) malloc (200*sizeof(char));



    fd_set      rset;

    FD_ZERO(&rset);

    int         maxfdp1;



    while (1)

    {

      FD_SET(fileno(stdin), &rset);

      FD_SET(net_socket1, &rset);

      FD_SET(net_socket2, &rset);

      maxfdp1 = (fileno(stdin)>net_socket1)?fileno(stdin):net_socket1;
      maxfdp1 = (maxfdp1>net_socket2)?maxfdp1:net_socket2;
      maxfdp1 = maxfdp1+1;

      select(maxfdp1, &rset, NULL, NULL, NULL);

      if (FD_ISSET(net_socket1, &rset))
      {  // socket is readable
            if (recv(net_socket1, recv_data1, 200, 0) == 0)
            {
                printf("Server 1 terminated prematurely\n");
                break;
            }
            fputs(recv_data1, stdout);
        }

      if (FD_ISSET(net_socket2, &rset))
      {
	      if(recv(net_socket2, recv_data2, 200, 0) == 0)
	      {
		      printf("Server 2 terminated prematurely\n");
		      break;
	      }
	      fputs(recv_data2, stdout);
      }

      if(FD_ISSET(fileno(stdin), &rset))

      {
        ch = fgets(send_data, 200, stdin);

  	    if(ch == NULL)
  	    {
  		    printf("user has terminated the connection.\n");
  		    break;     /* all done */
  	    }
        write(net_socket1, send_data, strlen(send_data));
        write(net_socket2, send_data, strlen(send_data));
      }

      //FD_ZERO(&rset);

    }

    free(send_data);

    free(recv_data1);

    free(recv_data2);

    close(net_socket1);

    close(net_socket2);

    return(0);

}
