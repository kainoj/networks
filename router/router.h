// Przemysław Joniak, 282751

#ifndef ROUTER_INCLUDE
#define ROUTER_INCLUDE

#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <errno.h>

#define VECT_SIZE 32

#pragma pack(1)	// prevents from struct alignment
typedef struct neigh_info {
	struct in_addr ip;
	char m_len; // massk len
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

// utils_io.h
void readConfig();
void printDistVecotr();

// utils_ip.h
struct in_addr getIp(char cidr[]);
struct in_addr getBroadcast(struct in_addr ip, char mask_len);
char getMaskLen(char cidr[]);

// send.h
bool Sendto(size_t i, size_t j); // true if a i-th packet was sent
                                 // to j-th broadcast address successfully
void send();                     // sends the whole vector


#endif
