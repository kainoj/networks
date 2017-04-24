// Przemysław Joniak, 282751

#include "router.h"

int n;
std::vector<neigh> dvct;
std::vector<neigh_info> neigh_nets;
std::vector<int> neigh_nets_cutdown;
int sockfd_rcv;
struct sockaddr_in srvr_adrs;


void printBin(uint32_t n) {
	
	int r[32] = {0};
	int j=1;
	while(n) {
		r[32-j] = n&1;
		n>>=1;
		j++;
	};
	for(int i=0; i<32; i++) {
		printf("%d", r[i]);
		if(i==7 || i==15 || i==23) printf(".");
	}
	printf("\n");
}


int main() {
	initRcvSock();
	readConfig();
	
	while(1) {
		printDistVecotr();
		send();
		receive(); // and update vector
		chechUnreachability();
	}
	close(sockfd_rcv);
	return 0;
}