#include "router.h"

void update(neigh_info msg, struct in_addr via_net) {
	unsigned long dist_to_sender = INF;
	unsigned long msg_dist = (long) msg.dist;
	unsigned long dvct_dist;

	for(size_t i=0; i<neigh_nets.size(); i++) {
		if(getNetAddress(neigh_nets[i].ip, neigh_nets[i].m_len).s_addr == via_net.s_addr) {
			dist_to_sender = neigh_nets[i].dist;
		}
	}
	for(size_t i=0; i<dvct.size(); i++) {
		if(dvct[i].info.ip.s_addr == msg.ip.s_addr) {
			dvct_dist = dvct[i].info.dist;
			
			if( msg.dist != INF ) {
				if( msg_dist + dist_to_sender < dvct_dist ) {
					dvct[i].info       = msg;
					dvct[i].info.dist += dist_to_sender;
					dvct[i].via        = via_net;
				}
				dvct[i].inf_cntr = INF_LIFETM;
			}
			else {
				if( msg_dist + dist_to_sender >= INF) {
					if(!dvct[i].directly)
						dvct[i].info.dist = INF;
				}
				else
					dvct[i].info.dist += dist_to_sender;
			}
			return;
		}
	}
	if(msg.dist == INF) return;
	// It's brand new entry, push it!
	neigh new_neigh;
	new_neigh.info      = msg;
	new_neigh.info.dist+= dist_to_sender; 
	new_neigh.directly  = false;
	new_neigh.reachable = true;
	new_neigh.via       = via_net;
	new_neigh.inf_cntr  = INF_LIFETM;
	dvct.push_back(new_neigh);
}