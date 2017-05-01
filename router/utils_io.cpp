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
		ne.directly   = ne.reachable = true;
		ne.inf_cntr   = INF_LIFETM;
		ne.via.s_addr = 0;
		dvct.push_back( ne );
		neigh_nets.push_back( {getIp(cidr), getMaskLen(cidr), dist} );
		neigh_nets_cutdown.push_back( NEIGH_LIFETM );
	}
}
 
void printDistVecotr() {
	for(size_t i=0; i<dvct.size(); i++) {
		printf("%s/%d\t", inet_ntoa(dvct[i].info.ip), dvct[i].info.m_len );
		if( dvct[i].reachable ) {
			if(dvct[i].info.dist < INF)
				printf("distance %u\t", dvct[i].info.dist);
			else printf("distance INF\t");
		}
		else printf("unreachable\t");
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
		if( neigh_nets_cutdown[i]-- <= 0) {
			dvct[i].reachable = false;
			// Search the vector for connections through unreachable net
			struct in_addr unrchbl_net = getNetAddress(dvct[i].info.ip, dvct[i].info.m_len);
			for(size_t j=0; j<dvct.size(); j++) {
				if( unrchbl_net.s_addr == getNetAddress(dvct[j].via, dvct[j].info.m_len).s_addr  ) {
					dvct[j].info.dist = INF;
				}
			}	
		}
		//else {
		//	dvct[i].reachable = true;
		//	}
	}

	// deal with infinities
	for(size_t i=0; i<dvct.size(); i++) {
		if(dvct[i].directly == false && dvct[i].info.dist == INF) {
			if( dvct[i].inf_cntr-- <=0 ) {
				dvct.erase(dvct.begin()+i);
				i--;
			}
		}
	}
}