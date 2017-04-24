// Przemysław Joniak, 282751

#include "router.h"

void readConfig() {
	char cidr[15], tmp[16];
	uint32_t dist;
	neigh ne;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%s %s %d", cidr, tmp, &dist);
		ne.info.ip    = getNetAddress(getIp(cidr), getMaskLen(cidr));
		ne.info.m_len = getMaskLen(cidr);
		ne.info.dist  = dist;
		ne.directly = ne.reachable = true;
		dvct.push_back( ne );
		neigh_nets.push_back( {getIp(cidr), getMaskLen(cidr), dist} );
		neigh_nets_cutdown.push_back( NEIGH_LIFETM );
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
	printf("\n");
}

void Error(const char *msg) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errno)); 
	exit(EXIT_FAILURE);
}


void chechUnreachability() {

	// Decrement lifetime cutdown
	for(size_t i=0; i<neigh_nets_cutdown.size(); i++){
		printf("%s -- %d   left\n", inet_ntoa(dvct[i].info.ip), neigh_nets_cutdown[i]);
		if( neigh_nets_cutdown[i]-- <= 0) {
			dvct[i].reachable = false;
			printf("%s became unreachable\n", inet_ntoa(dvct[i].info.ip) );
		}
	}
}