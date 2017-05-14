#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

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
	if (bind(fd, (struct sockaddr*)saddr, saddr_len) < 0)
		ERROR ("bind error");
}
