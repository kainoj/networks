#include "traceroute.h"

int receive(int *sockfd, struct icmphdr *senthdrs, reply *replies) {
	int packets_received = 0;	

	struct sockaddr_in  sender;	
	socklen_t           sender_len = sizeof(sender);
	u_int8_t            buffer[IP_MAXPACKET];

	fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (*sockfd, &descriptors);

	struct timeval tv;   // selects() overwrites tv values
	tv.tv_sec = TIMEOUT; // seconds
	tv.tv_usec = 0;      // microseconds

	// packets_left decrements on receiving 1 of 3 sent packets
	// packets_left is set to 0 on select()'s timeout
	int packets_left = 3;
	int ready;

	while(packets_left > 0) {

		ready = select ((*sockfd)+1, &descriptors, NULL, NULL, &tv);
		
		if(ready < 0) {
			Error("select()");	
		}
		else if(ready==0) { 
			is_timeout = true;
			return packets_received;
		}
		else {
			ssize_t packet_len = recvfrom (*sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
			if (packet_len < 0) Error("recvfrom");
			
			char sender_ip_str[20]; 
			if( inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str)) == NULL) Error("inet_ntop()");

			if( comparehdrs(senthdrs, buffer) ) {
				strcpy(replies[packets_received].ip, sender_ip_str);

				if( gettimeofday(&reci_time, NULL) <0) Error("gettimeofday()");
				replies[packets_received].time = reci_time.tv_usec - send_time.tv_usec; 
				if( replies[packets_received].time < 0 ) printf("OPPPPPPPPPPPPPPPPPS\n");
				packets_received++;
				packets_left--;
			}			
		}
	}
	return packets_received;
}