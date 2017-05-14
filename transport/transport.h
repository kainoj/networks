#ifndef TRANSPORT
#define TRANSPORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(1); }

#define DATAGRAM_LEN 1000 // [bytes], an arbitraty value from 1 to 1000
#define WIN_SIZE 100

int Port;
char FileName[50];
int TotalDataSize; // #bytes to be downloaded
extern const char *SERVER_IP;

int sockfd_send;
int sockfd_recv;
struct sockaddr_in server_address_send;
struct sockaddr_in server_address_recv;

typedef struct Window {
  int start;
  int length;
  bool received;
  char data[DATAGRAM_LEN];
} Window;

extern Window window[WIN_SIZE];
int sockfd;


void init_socket_send(int port);
void send_request(int segment_number, char *datagram_len_str);

void init_socket_recv(int port);
void init_socket_recv(int port);



#endif
