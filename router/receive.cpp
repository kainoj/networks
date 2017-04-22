// Przemysław Joniak, 282751

#include "router.h"

void initRcvSock() {
	sockfd_rcv = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd_rcv < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		exit(EXIT_FAILURE);
	}
	
	bzero (&srvr_adrs, sizeof(srvr_adrs));
	srvr_adrs.sin_family      = AF_INET;
	srvr_adrs.sin_port        = htons(12345);
	srvr_adrs.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind (sockfd_rcv, (struct sockaddr*)&srvr_adrs, sizeof(srvr_adrs)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno)); 
		exit(EXIT_FAILURE);
	}
}

void receive() {
	int ready = 0;

	struct sockaddr_in 	sender;	
	socklen_t 			sender_len = sizeof(sender);
	u_int8_t 			buffer[IP_MAXPACKET+1];
	
	fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (sockfd_rcv, &descriptors);
	struct timeval tv = { ROUND_LEN, 0 };

	ready = select(sockfd_rcv+1, &descriptors, NULL, NULL, &tv);
	if(ready < 0) Error("select()");
	if(ready == 0) return;

	

	ssize_t datagram_len = recvfrom (sockfd_rcv, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
	if (datagram_len < 0) Error("recvfrom()"); 

	char sender_ip_str[20]; 
	inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
	printf ("Received UDP packet from IP address: %s, port: %d\n", sender_ip_str, ntohs(sender.sin_port));

	buffer[datagram_len] = 0;
	printf("%ld-byte message: +%s+\n", datagram_len, buffer);
	
	char* reply = "Thank you!";
	ssize_t reply_len = strlen(reply);
	if (sendto(sockfd_rcv, reply, reply_len, 0, (struct sockaddr*)&sender, sender_len) != reply_len) {
		Error("sendto()");		
	}

	fflush(stdout);
}