#include "router.h"

void update(neigh_info msg, struct in_addr via_Net) {
	uint32_t dist_to_sender = INF;

	for(size_t i=0; i<brdcsts.size(); i++) {
		if( brdcsts[i].first.s_addr == via_Net.s_addr) {
			dist_to_sender = brdcsts[i].second;
			break;
		}
	}

	for(size_t i=0; i<dvct.size(); i++) {
		if (dvct[i].info.ip.s_addr == msg.ip.s_addr) {
			printf("Znalazlem taki sam\n");
			//czy lepuiej?
				//update
			return;
		}
	}
	// It's brand new entry, push it!
	neigh new_neigh;
	new_neigh.info      = msg;
	new_neigh.info.dist+= dist_to_sender; 
	new_neigh.directly  = false;
	new_neigh.reachable = true;
	new_neigh.via       = via_Net;
	dvct.push_back(new_neigh);

}