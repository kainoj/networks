#include "router.h"

void update(neigh_info msg, struct in_addr via_net) {
	uint32_t dist_to_sender = INF;

	for(size_t i=0; i<neigh_nets.size(); i++) {
		if(getNetAddress(neigh_nets[i].ip, neigh_nets[i].m_len).s_addr == via_net.s_addr) {
			dist_to_sender = neigh_nets[i].dist;
		}
	}
	//printf("wysylajacy: %s\n", inet_ntoa(via_net) );
	//printf("odleglosc do wysylajacego: %u\n", dist_to_sender);

	for(size_t i=0; i<dvct.size(); i++) {
		if (dvct[i].info.ip.s_addr == msg.ip.s_addr) {
			//printf("Znalazlem taki sam\n");
			if( dvct[i].info.dist > msg.dist + dist_to_sender) {
				dvct[i].info = msg;
				dvct[i].via  = via_net;
			}
			return;
		}
	}
	// It's brand new entry, push it!
	neigh new_neigh;
	new_neigh.info      = msg;
	new_neigh.info.dist+= dist_to_sender; 
	new_neigh.directly  = false;
	new_neigh.reachable = true;
	new_neigh.via       = via_net;
	dvct.push_back(new_neigh);

}