#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 59000

int main(int argc, char **argv)
{
	int fd;
	const char *hname = "localhost";
	struct hostent *hostptr;
	struct sockaddr_in serveraddr, clientaddr;
	int addrlen;
	
	if (argc > 1)
	{
		hname = argv[1];
	}
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	hostptr = gethostbyname(hname);
	
	memset((void *)&serveraddr, '\0', sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = ((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
	serveraddr.sin_port = htons((unsigned short)PORT);
	
	addrlen = sizeof(serveraddr);  
	
	for (;;)
	{
		char inbuff[100];
		if (scanf("%s", inbuff) == EOF)
		{
			break;
		}
	
		inbuff[99] = '\0';
		
		sendto(fd, inbuff, strlen(inbuff) + 1, 0, (struct sockaddr *)&serveraddr, addrlen);
		
		char buffer[4 << 10];
		recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serveraddr, &addrlen);
		buffer[sizeof(buffer) - 1] = '\0';
		printf("%s\n", buffer);
	}
	
	close(fd);
	
	return 0;
}
