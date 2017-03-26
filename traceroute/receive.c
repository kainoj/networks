#include "traceroute.h"

void print_as_bytes (unsigned char* buff, ssize_t length) {
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);	
}

void print_as_bytes_ip_data (unsigned char* buff, ssize_t length) {
	if(*buff == 0) printf("type: echo replay\n");
	if(*buff == 11) printf("type: time exceeded\n");
	print_as_bytes(buff, length);	
}


//////////////////////


int receive(int *sockfd, struct icmphdr *senthdrs) {
	
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
			fprintf(stderr, "select(): error receivning sockets\n"); 
			return EXIT_FAILURE;	
		}
		else if(ready==0) { 
			printf("todo: TIMEOUT\n");	
			packets_left=0; }
		else {
			ssize_t packet_len = recvfrom (*sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
			if (packet_len < 0) {
				fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
				return EXIT_FAILURE;
			}


			char sender_ip_str[20]; 
			inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

			printf ("Received IP packet with ICMP content from: %s\n", sender_ip_str);

			////
			if( comparehdrs(senthdrs, buffer) ) {
				printf("Dopasowalem naglowek! \n");
				packets_left--;
			}

			
		}
	}
	return 0;
}