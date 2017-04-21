#include "router.h"

struct dvector {
	struct in_addr ip;
	char m_len; // mask length
	uint32_t dist;
	bool directly;
	struct in_addr via;
} dvector[VECT_SIZE];


void readConfig() {

	char cidr[15], tmp[16];
	int dist;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%s %s %d", cidr, tmp, &dist);

		dvector.ip = getIp(cidr);
		//dvector.m_len = ...
		dvector.dist = dist;
		dvector.directly = true;
	}
}

void printVector() {

	
}


int main() {

	//printf("s = %lu\n", sizeof(dvector));

	

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
	return 0;
}