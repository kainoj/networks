#ifndef WRAPPERS
#define WRAPPERS

int Socket(int family, int type, int protocol);
void Sendto(int fd, char *msg, int msg_len, int flags, struct sockaddr* saddr, int saddr_len);
void Bind(int fd, struct sockaddr *saddr, socklen_t saddr_len);

#endif
