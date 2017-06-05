#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUFFSIZE 5000000	// 5mb //10 MB
#define TIMEOUT_SEC 0 //  sec
#define TIMEOUT_USEC 733333

class Server {
  int port;
  int sockfd;
  int conn_sockfd;
  char buffer[BUFFSIZE+1];
  std::string dir;
  struct timeval tv;
  struct sockaddr_in server_address;
  fd_set descriptors;


  public:
    Server(int Port, std::string dir);
    void receive();

  private:
    void initSelect();

    int Socket(int family, int type, int protocol);
    void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen);
    void Connect(int fd, const struct sockaddr_in *sa, socklen_t salen);
    int Accept(int fd, struct sockaddr_in *sa, socklen_t *salenptr);
    void Listen(int fd, int backlog);
    ssize_t Recv(int fd, char *ptr, size_t nbytes, int flags);
    void Send(int fd, char *ptr, int nbytes, int flags);
    void Close(int fd);
    int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

};


#endif
