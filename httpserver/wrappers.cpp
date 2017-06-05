// Przemysław Joniak, 282751
// Modified mbi's sockwrap

#include "server.h"

#define ERROR(str) { fprintf(stderr, "Server error: %s: %s\n", (str), strerror(errno)); exit(1); }

int Server::Socket(int family, int type, int protocol) {
	int	n = socket(family, type, protocol);
	if ( n < 0) ERROR ("socket error");
	return n;
}

void Server::Bind(int fd, const struct sockaddr_in *sa, socklen_t salen) {
	if (bind(fd, (struct sockaddr*)sa, salen) < 0)
		ERROR ("bind error");
}

void Server::Connect(int fd, const struct sockaddr_in *sa, socklen_t salen) {
	if (connect(fd, (struct sockaddr*)sa, salen) < 0)
		ERROR ("connect error");
}

int Server::Accept(int fd, struct sockaddr_in *sa, socklen_t *salenptr) {
	int n = accept(fd, (struct sockaddr*)sa, salenptr);
    if ( n < 0) ERROR ("accept error");
    return n;
}

void Server::Listen(int fd, int backlog) {
    if (listen(fd, backlog) < 0)
		ERROR ("listen error");
}

ssize_t Server::Recv(int fd, char *ptr, size_t nbytes, int flags) {
	int n = recv(fd, ptr, nbytes, flags);
	if ( n < 0) ERROR ("recv error");
	ptr[n] = 0;
	return n;
}

void Server::Send(int fd, char *ptr, int nbytes, int flags) {
	// to niekoniecznie jest blad!
	if (send(fd, ptr, nbytes, flags) < nbytes)
		ERROR ("send error");
}

void Server::Close(int fd) {
	if (close(fd) < 0) ERROR ("close error");
}

int Server::Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    int n = select(nfds,readfds,writefds,exceptfds,timeout);
    if ( n < 0) ERROR ("select error");
    return n;
}
