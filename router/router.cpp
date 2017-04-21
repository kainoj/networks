#include "router.h"

std::vector<neigh> dvct;


void readConfig() {
	char cidr[15], tmp[16];
	int dist, n;
	neigh ne;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%s %s %d", cidr, tmp, &dist);
		ne.ip    = getIp(cidr);
		ne.m_len = getMaskLen(cidr);
		ne.dist  = dist;
		ne.directly = true;
		dvct.push_back( ne );
	}
}


void printDistVecotr() {
	for(size_t i=0; i<dvct.size(); i++) {
		printf("%s/%d\t", inet_ntoa(dvct[i].ip), dvct[i].m_len );
		printf("distance %u\t", dvct[i].dist);
		if(dvct[i].directly)
			printf("connected directly\n");
		else
			printf("via %s\n", inet_ntoa(dvct[i].via));
	}
}


int main() {
	readConfig();
	printDistVecotr();
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