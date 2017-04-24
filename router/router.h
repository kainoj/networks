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

#define ROUND_LEN 4     // [sec]
#define INF 4294967295U // 2^32 - 1
#define PORT 54321

                        // All data but IPs are stored in host byte order
#pragma pack(1)         // Data to be sent/received
typedef struct neigh_info {
	struct in_addr ip;  // IP of a {NETWORK | BROADCAST}
	char m_len;         // Net mask length
	uint32_t dist;      // Distance to the network
} neigh_info;           
#pragma pack()          // Prevents from struct alignment

typedef struct neigh {  // Full single entry in a distance vector
	neigh_info info;    // Core info of the entry
	bool directly;      // True iff net is connected directly
	bool reachable;     // True iff net is reachable
	struct in_addr via; // Set iff net is not connected directly;
	                    // IP address of the first net on the way
} neigh;

extern int n;           // First n entries are my neighbours
extern std::vector<neigh> dvct;               // Distance vector
extern std::vector<neigh_info> neigh_nets;    // Nets I'm directly connected with
                                              // IP = host IP, net address to be computed!!!
extern std::vector<struct in_addr> my_neighs; // My IP addresses 
                                              //  ^probably i won't need it anymore
extern int sockfd_rcv;
extern struct sockaddr_in srvr_adrs;

// utils_io.h
void readConfig();
void printDistVecotr();
void Error(const char *msg);     // Error wrapper

// utils_ip.h
struct in_addr getIp(char cidr[]);
struct in_addr getBroadcast(struct in_addr ip, char mask_len);
struct in_addr getNetAddress(struct in_addr ip, char mask_len);
char getMaskLen(char cidr[]);

// send.h
bool Sendto(size_t i, size_t j); // True if a i-th packet was sent
                                 // to j-th broadcast address successfully
void send();                     // Sends the whole vector

// receive.h
void initRcvSock();
void receive();

// update.h
void update(neigh_info msg, struct in_addr via_net);

#endif
