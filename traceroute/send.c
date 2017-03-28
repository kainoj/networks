// Przemysław Joniak, 282751

#include "traceroute.h"

void icmp_send(int sockfd, struct icmphdr *icmp_header, char * ip_addr, int ttl) {

	struct sockaddr_in recipient;
	bzero (&recipient, sizeof(recipient));
	recipient.sin_family = AF_INET;
	if(inet_pton(AF_INET, ip_addr, &recipient.sin_addr) <=0 ) Error("inet_pton()");
	
	if(setsockopt (sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) < 0) Error("setsockopt()");

	ssize_t bytes_sent = sendto (
		 sockfd,
		 icmp_header,
		 sizeof(*icmp_header),
		 0,
		 (struct sockaddr*)&recipient,
		 sizeof(recipient)
	);
	if(bytes_sent<0) Error("sendtop()");
}
