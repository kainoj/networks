// Przemysław Joniak, 282751

#include "router.h"

int n;
std::vector<neigh> dvct;
std::vector<neigh_info> neigh_nets;
std::vector<struct in_addr> my_neighs;
int sockfd_rcv;
struct sockaddr_in srvr_adrs;

int main() {
	initRcvSock();
	readConfig();

	while(1) {
		printDistVecotr();
		send();
		receive(); // and update vector
	}
	close(sockfd_rcv);
	return 0;
}