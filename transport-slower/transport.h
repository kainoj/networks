#ifndef TRANSPORT
#define TRANSPORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(1); }

#define DATAGRAM_LEN 1000 // [bytes], an arbitraty value from 1 to 1000
#define WIN_SIZE 100
#define TIMEOUT_SEC 0 // [seconds]
#define TIMEOUT_USEC 100000 // [microseconds]

int  Port;
char FileName[50];
int  TotalDataSize; // #bytes to be downloaded
extern const char *SERVER_IP;

int sockfd;
struct sockaddr_in server_address;
FILE * pFile;

void init_socket(int port);
void send_request(char *request_msg);
bool receive(char *response_msg, int datagram_len);

#endif
