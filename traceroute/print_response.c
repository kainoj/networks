#include "traceroute.h"

void print_response(int ttl, int packets, reply *replies) {

	printf("%d. ", ttl);
	if( packets == 0) {
		printf("*\n");
		return;
	}

	long mean_time = 0;
	printf(">>>>>>>>>>>>>>>>>>>>>>\n");
	for(int i=0; i<packets; i++) {
		mean_time += replies[i].time;
		printf("ip: %s\ttime: %ld ms\n", replies[i].ip, replies[i].time/1000);
	}
	
	if(packets == 1) {
		printf("%s \n", replies[0].ip);
	}


	if(packets < 0) printf("\t???\n");
		else printf("\t%.2f\n", (1.0*mean_time)/(1000.0*packets) );
}	