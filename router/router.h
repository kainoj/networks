// Przemysław Joniak, 282751

#ifndef ROUTER_INCLUDE
#define ROUTER_INCLUDE

#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <errno.h>

#define VECT_SIZE 32
#define ROUND_LEN 3 // sec

#pragma pack(1)	// prevents from struct alignment
typedef struct neigh_info {
	struct in_addr ip;
	char m_len; // mask len
	uint32_t dist;
} neigh_info;
#pragma pack()

typedef struct neigh {
	neigh_info info;
	bool directly;
	bool reachable;
	struct in_addr via;
} neigh;

extern std::vector<neigh> dvct;
extern std::vector<struct in_addr> brdcsts;
extern struct timeval last_round;
extern int sockfd_rcv;
extern struct sockaddr_in srvr_adrs;

// utils_io.h
void readConfig();
void printDistVecotr();
void printDistVectElem(size_t i);
void initTimer();
bool isNextRound();
void Error(const char *msg); // error wrapper

// utils_ip.h
struct in_addr getIp(char cidr[]);
struct in_addr getBroadcast(struct in_addr ip, char mask_len);
char getMaskLen(char cidr[]);

// send.h
bool Sendto(size_t i, size_t j); // true if a i-th packet was sent
                                 // to j-th broadcast address successfully
void send();                     // sends the whole vector


// receive.h
void initRcvSock();
void receive();


#endif
