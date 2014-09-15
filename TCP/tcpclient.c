#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 58000

int main()
{
  int fd, newfd;
  struct hostent *hostptr;
  struct sockaddr_in serveraddr, clientaddr;
  int clientlen;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  hostptr = gethostbyname("localhost");

  memset((void *)&serveraddr, '\0', sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = ((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
  serveraddr.sin_port = htons((unsigned short)PORT);

  connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

  write(fd, "hello", 6);
  printf("[Client] Sent: Yes\n");

  char buf[20];
  read(fd, buf, 8); // expect "Close"

  printf("[Client] Received: %s\n", buf);

  close(fd);

  return 0;
}
