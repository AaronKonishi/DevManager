#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/hidraw.h>
#include <linux/netlink.h>

int main(void)
{
	int sockfd = -1;
	int recv_len = 0;
	char buffer[1024];
	struct sockaddr_nl socket_nl;

	sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
	if(sockfd < 0)
	{
		printf("Error : can't create socket.\n");
		return -1;
	}

	memset(&socket_nl, 0, sizeof(socket_nl));
	socket_nl.nl_family = AF_NETLINK;
	socket_nl.nl_pid = getpid();
	socket_nl.nl_groups = 1;

//	setsockopt(socketfd,SOL_SOCKET,SO_RCVBUF,&buffersize,sizeof(buffersize));

	if(bind(sockfd,(struct sockaddr*)&socket_nl,sizeof(socket_nl)) < 0)
	{
		printf("ERROR[%s:%d]: cannot bind socket .\n",__FILE__,__LINE__);
		close(sockfd);
		return -1; 
	}

	while(1)
	{
		memset(buffer, 0, sizeof(buffer));
		recv_len = recv(sockfd, buffer, sizeof(buffer), 0);
		if(recv_len > 0)
		{
			printf("recv:%s\n",buffer);
		}
	}

	close(sockfd);

	return 0;
}
