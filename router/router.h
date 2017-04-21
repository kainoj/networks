// Przemysław Joniak, 282751

#ifndef ROUTER_INCLUDE
#define ROUTER_INCLUDE

#include <stdio.h>
#include <string.h>
#include <vector>
#include <arpa/inet.h>

#define VECT_SIZE 32

struct in_addr getIp(char cidr[]);
struct in_addr getBroadcast(struct in_addr ip, char mask_len);
char getMaskLen(char cidr[]);

typedef struct neigh {
	struct in_addr ip;
	char m_len; // mask len
	uint32_t dist;
	bool directly;
	struct in_addr via;
} neigh;


#endif
