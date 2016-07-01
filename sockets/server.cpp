#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT_NUM 9889

using namespace std;

void die(string msg)
{
  perror(msg.c_str());
  exit(1);
}

void readFromSocket() {
  int sockfd, newsockfd;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    die("ERROR opening socket");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT_NUM);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
   die("ERROR on binding");
  }

  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0) {
   die("ERROR on accept");
  }

  bzero(buffer,256);
  n = read(newsockfd,buffer, 255);
  if (n < 0) {
    die("ERROR reading from socket");
  }

  printf("Here is the message: %s\n", buffer);

  n = write(newsockfd,"I got your message",18);
  if (n < 0) {
    die("ERROR writing to socket");
  }

  close(newsockfd);
  close(sockfd);
}


int main(void) {
  readFromSocket();
  return 0;
}
