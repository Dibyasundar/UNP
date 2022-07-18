// int getsockopt(int socket,int level, int optname, void *optval, socklen_t *optlen);
// prog to see the default value of send buffer size in TCP.
// int setsockopt(int socket, int level, int opt, void *optval, socklen_t optlen)
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
int main()
{

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	int val, val_len;
	printf("================== BEFORE ======================\n");
	val = 0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &val_len);
	printf("default send buffer size in TCP: %d\n", val);
	val =0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val , &val_len);
	printf("default recv buffer size in TCP : %d\n", val);

	val = 2;
	setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, sizeof(val));
	val =2;
	setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val));
	printf("==================== AFTER =====================\n");
	val = 0;
        val_len = sizeof(val);
        getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &val_len);
        printf("Current send buffer size in TCP: %d\n", val);
        val =0;
        val_len = sizeof(val);
        getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val , &val_len);
        printf("Current recv buffer size in TCP : %d\n", val);

	close(fd);


	fd = socket(AF_INET, SOCK_DGRAM, 0);
	val=0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &val_len);
	printf("default send buffer size in UDP : %d\n", val);
	val =0;
        val_len = sizeof(val);
        getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val , &val_len);
        printf("default recv buffer size in UDP : %d\n", val);
	close(fd);

	return(0);
}
	
