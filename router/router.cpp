// Przemysław Joniak, 282751

#include "router.h"

int n;
std::vector<neigh> dvct;
std::vector<struct in_addr> brdcsts;
std::vector<struct in_addr> my_neighs;
struct timeval last_round;
int sockfd_rcv;
struct sockaddr_in srvr_adrs;

int main() {
	initRcvSock();
	readConfig();

	while(1) {
		printDistVecotr();
		send();
		receive();
	}
	close(sockfd_rcv);
	return 0;
}