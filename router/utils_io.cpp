// Przemysław Joniak, 282751

#include "router.h"

void readConfig() {
	char cidr[15], tmp[16];
	int dist, n;
	neigh ne;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%s %s %d", cidr, tmp, &dist);
		ne.info.ip    = getIp(cidr);
		ne.info.m_len = getMaskLen(cidr);
		ne.info.dist  = dist;
		ne.directly = ne.reachable = true;
		dvct.push_back( ne );
		brdcsts.push_back( getBroadcast(ne.info.ip, ne.info.m_len) );
	}
}

void printDistVecotr() {
	for(size_t i=0; i<dvct.size(); i++) {
		printf("%s/%d\t", inet_ntoa(dvct[i].info.ip), dvct[i].info.m_len );
		printf("%s %u\t", dvct[i].reachable? "distance" : "unreachable", dvct[i].info.dist);
		if(dvct[i].directly)
			printf("connected directly\n");
		else
			printf("via %s\n", inet_ntoa(dvct[i].via));
	}
}