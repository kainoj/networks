#include "traceroute.h"

void print_response(int ttl, int packets, reply *replies) {

	printf("%d.   ", ttl);
	if( packets == 0) {
		printf("*\n");
		return;
	}
	long mean_time = 0;
	
	for(int i=0; i<packets; i++) {
		mean_time += replies[i].time;
		//printf("\tip: %s,  time: %ld ms\n", replies[i].ip, replies[i].time/1000);
	}

	if(packets == 1) printf("%s ", replies[0].ip);

	if(packets == 2) {
		printf("%s  ", replies[0].ip);
		if( strcmp(replies[1].ip, replies[0].ip))
			printf("%s  ", replies[1].ip);
	}
	if(packets == 3) {
		printf("%s  ", replies[0].ip);

		if( strcmp(replies[1].ip, replies[0].ip) )
			printf("%s  ",  replies[1].ip);

		if( strcmp(replies[2].ip, replies[1].ip) && strcmp(replies[2].ip, replies[0].ip) )
			printf("%s  ", replies[2].ip );
	}
	
	if(is_timeout) {
		printf("\t???\n");	
		is_timeout = false;
	}
	else 
		printf("\t%.2f\n", (1.0*mean_time)/(1000.0*packets) );
}	