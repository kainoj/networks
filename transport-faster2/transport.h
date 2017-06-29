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
#define WIN_SIZE 500
#define TIMEOUT_SEC 0 // [seconds]
#define TIMEOUT_USEC 10000 // [microseconds]

typedef struct Window {
  int start_byte;
  int data_length;
  bool received;
  char data[DATAGRAM_LEN+20];
} Window;

Window window[WIN_SIZE];
int rcvd;
int byte_lower_bound;

int  Port;
char FileName[50];
int  TotalDataSize; // #bytes to be downloaded
extern const char *SERVER_IP;

int sockfd;
struct sockaddr_in server_address;
FILE * pFile;

void init_socket(int port);
void send_request(int win_size);
bool receive();

void slideWindow(int start_win_byte);
void storeDatagram(int start_byte, char *buffer);
void winToFile(int win_size);
int winCrumbs(int last_byte, int left_bytes, int left_datagrams);

#endif
