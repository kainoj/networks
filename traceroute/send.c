#include "traceroute.h"


int icmp_send(int sockfd, struct icmphdr *icmp_header, char * ip_addr, int ttl) {



	struct sockaddr_in recipient;
	bzero (&recipient, sizeof(recipient));
	recipient.sin_family = AF_INET;
	inet_pton(AF_INET, ip_addr, &recipient.sin_addr); 
	

	setsockopt (sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

	ssize_t bytes_sent = sendto (
		 sockfd,
		 icmp_header,
		 sizeof(*icmp_header),
		 0,
		 (struct sockaddr*)&recipient,
		 sizeof(recipient)
	);
	//printf("Wyslano bajtow:ld\n", bytes_sent);
}

