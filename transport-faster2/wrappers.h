#ifndef WRAPPERS
#define WRAPPERS

#include <sys/select.h>

int  Socket(int family, int type, int protocol);
void Sendto(int fd, char *msg, int msg_len, int flags, struct sockaddr* saddr, int saddr_len);
void Bind(int fd, struct sockaddr *saddr, socklen_t saddr_len);
int  Select(int fds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
ssize_t Recvfrom(int fd, char *ptr, size_t nbytes, int flags, struct sockaddr *sender, socklen_t *sender_len);
size_t  FWrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
FILE   *FOpen(char *path,  char *mode);

#endif
