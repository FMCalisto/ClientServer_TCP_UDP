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

  bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

  listen(fd, 5);

  clientlen = sizeof(clientaddr);
  newfd = accept(fd, (struct sockaddr *)&clientaddr, &clientlen);

  char buf[20];
  read(newfd, buf, 6); // expect "Yes"
  
  printf("[Server] Received: %s\n", buf);

  write(newfd, "Close", 8); // send "Close"
  
  printf("[Server] Sent: Close\n");

  close(fd);
  close(newfd);

  return 0;
}
