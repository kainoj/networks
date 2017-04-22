// Przemysław Joniak, 282751

#include "router.h"

std::vector<neigh> dvct;
std::vector<struct in_addr> brdcsts;
struct timeval last_round;
int sockfd_rcv;
struct sockaddr_in srvr_adrs;

int main() {
	initTimer();
	initRcvSock();
	readConfig();

	printDistVecotr();	
	while(1) {
		
		//if(isNextRound()) {
			//send();
			printf("bam!\n");
		//}
		receive();

	}
	
	close (sockfd_rcv);
	return 0;
}



/*  
	//char cidr[] = "192.168.1.34/24";	
	struct in_addr ip, mask, brdcst;
	ip     = getIp(cidr);
	mask   = getMask(cidr);
	brdcst = getBroadcast(ip, mask);
	printf("ip=(%s)\n",   inet_ntoa(ip) );
	printf("mask=(%s)\n", inet_ntoa(mask) );
	printf("brdcs=(%s)\n",inet_ntoa(brdcst));
*/