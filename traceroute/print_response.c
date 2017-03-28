// Przemysław Joniak, 282751

#include "traceroute.h"

void print_response(int ttl, int packets, reply *replies) {

	if(ttl < 10) printf(" ");

	printf("%d.  ", ttl);
	if( packets == 0) {
		printf("*\n");
		return;
	}
	float mean_time = 0;
	
	for(int i=0; i<packets; i++) {
		mean_time += replies[i].time;
		//printf("\tip: %s,  time: %f ms\n", replies[i].ip, replies[i].time); // 4 debug
	}

	if(packets == 1) printf("%s\t", replies[0].ip);

	if(packets == 2) {
		printf("%s\t", replies[0].ip);
		if( strcmp(replies[1].ip, replies[0].ip))
			printf("%s\t", replies[1].ip);
	}
	if(packets == 3) {
		printf("%s\t", replies[0].ip);

		if( strcmp(replies[1].ip, replies[0].ip) )
			printf("%s\t",  replies[1].ip);

		if( strcmp(replies[2].ip, replies[1].ip) && strcmp(replies[2].ip, replies[0].ip) )
			printf("%s\t", replies[2].ip );
	}
	
	if(is_timeout) {
		printf("???\n");	
		is_timeout = false;
	}
	else 
		printf("%.3f ms\n", mean_time/(1.0*packets) );
}	