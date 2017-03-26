#ifndef TRACEROUTE
#define TRACEROUTE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h> // PID

#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>


#define TTL 2
#define TIMEOUT 3
#define PACKETS 3


int PID;

u_int16_t compute_icmp_checksum (const void *buff, int length);

void icmp_send(int sockfd, struct icmphdr *icmp_header, char * ip_addr, int ttl);
void init_icmp_header(struct icmphdr *icmp_header);
void update_icmp_header(struct icmphdr *icmp_header, u_int16_t echo_seq );



#endif