#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

#include "wrappers.h"
#include "transport.h"

int Socket(int family, int type, int protocol) {
	int	n = socket(family, type, protocol);
	if ( n < 0) ERROR ("socket() error");
	return n;
}

void Sendto(int fd, char *msg, int msg_len, int flags, struct sockaddr  *saddr, int saddr_len) {
	if (sendto(fd, msg, msg_len, flags, saddr, saddr_len) != msg_len)
    ERROR ("sendto() error");
}

void Bind(int fd, struct sockaddr *saddr, socklen_t saddr_len) {
	if (bind(fd, saddr, saddr_len) < 0)
		ERROR ("bind() error");
}

int Select(int fds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    int n = select(fds, readfds, writefds, exceptfds, timeout);
    if(n < 0) ERROR ("select() error");
    return n;
}

//man recvfrom: 
//      recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t Recvfrom(int fd, char *ptr, size_t nbytes, int flags, struct sockaddr *sender, socklen_t *sender_len) {
	int n = recvfrom (fd, ptr, nbytes, flags, sender, sender_len);
	if(n < 0) ERROR ("recv() error");
	ptr[n] = 0;
	return n;
}
