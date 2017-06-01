#pragma once

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define ERROR(str) { fprintf(stderr, "%s\nStatus: %s\n", (str), strerror(errno)); exit(1); }

int Socket(int family, int type, int protocol);
void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr_in *sa, socklen_t salen);
int Accept(int fd, struct sockaddr_in *sa, socklen_t *salenptr);
void Listen(int fd, int backlog);
ssize_t Recv(int fd, char *ptr, size_t nbytes, int flags);
void Send(int fd, char *ptr, int nbytes, int flags);
void Close(int fd);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
