#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 58000

int main(int argc, char *argv[])
{
	int clientlen;
	int fd, newfd;
	
	char *hname = "localhost";
	
	struct hostent *hostptr;
	struct sockaddr_in serveraddr, clientaddr;
	
	if (argc > 1)
	{
		hname = argv[1];
	}
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	hostptr = gethostbyname(hname);
	
	memset((void *)&serveraddr, '\0', sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = ((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
	serveraddr.sin_port = htons((unsigned short)PORT);
	
	connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	
	for (;;)
	{
		char buf[100];
		if (scanf("%s", buf) == EOF)
		{
			break;
		}
		
		buf[99] = '\0';
		
		write(fd, buf, sizeof(buf) - 1);
		// printf("[Client] Sent: hello\n");
		
		printf("Server reply:\n");
		
		while (read(fd, buf, sizeof(buf) - 1) > 0)
		{
			printf("%s", buf);
		}
		
		printf("\n");
	}
	
	close(fd);
	
	return 0;
}
