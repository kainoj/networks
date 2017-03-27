#ifndef TRACEROUTE
#define TRACEROUTE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h> // PID
#include <stdbool.h>

#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define TTL 15
#define TIMEOUT 1
#define PACKETS 3

#define ONEuSEC 1000000 // 1 microsecond

int PID;

// reply received every iteration
typedef struct reply {
	long time;
	char ip[20];
} reply;


u_int16_t compute_icmp_checksum (const void *buff, int length);

void icmp_send(int sockfd, struct icmphdr *icmp_header, char * ip_addr, int ttl);
void init_icmp_header(struct icmphdr *icmp_header);
void update_icmp_header(struct icmphdr *icmp_header, u_int16_t echo_seq );

void print_icmp_header(struct icmphdr *icmp_header);

int receive(int *sockfd, struct icmphdr *senthdrs, reply *replies);


bool comparehdrs(struct icmphdr *sent_hdr, u_int8_t *buffer);

void print_response(int ttl, int packets, reply *replies);


#endif