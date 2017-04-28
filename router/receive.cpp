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
	srvr_adrs.sin_port        = htons(PORT);
	srvr_adrs.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind (sockfd_rcv, (struct sockaddr*)&srvr_adrs, sizeof(srvr_adrs)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno)); 
		exit(EXIT_FAILURE);
	}
}

void receive() {
	int ready = 0;

	struct sockaddr_in  sender;	
	socklen_t           sender_len = sizeof(sender);
	
	fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (sockfd_rcv, &descriptors);
	struct timeval tv = { ROUND_LEN, 0 };
	ssize_t datagram_len;
	char sender_ip_str[20]; 
	neigh_info msg;

	do {
		ready = select(sockfd_rcv+1, &descriptors, NULL, NULL, &tv);
		if(ready < 0) Error("select()");
		if(ready == 0) return;

		// Receive UDP packet
		datagram_len = recvfrom (sockfd_rcv, &msg, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
		if (datagram_len < 0) Error("recvfrom()"); 

		// Check if received packet wasn't sent by me
		bool isPacketMine = false;
		for(size_t i=0; i<neigh_nets.size(); i++) {
			if( sender.sin_addr.s_addr == neigh_nets[i].ip.s_addr ) {
				isPacketMine = true;
			}
		}
		if(isPacketMine) continue; // Do not execute code below, skip to next iteration

		// And match received IP packet with a network
		char m_len;
		size_t idx = 0;
		for(size_t i=0; i<neigh_nets.size(); i++) {     // Mask
			struct in_addr addrA = getNetAddress(sender.sin_addr, neigh_nets[i].m_len);
			for(size_t j=0; j<neigh_nets.size(); j++) { // Net
				if(addrA.s_addr == getNetAddress(neigh_nets[j].ip, neigh_nets[j].m_len).s_addr)  {
					m_len = neigh_nets[i].m_len;
					idx=i;
					//printf("%s -- %s -> %d \n", inet_ntoa(addrA), inet_ntoa(getNetAddress(neigh_nets[j].ip, neigh_nets[j].m_len)), neigh_nets[i].m_len );
				}
			}
		}
		neigh_nets_cutdown[idx] = NEIGH_LIFETM;
	
		inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
		msg.dist = ntohl(msg.dist);
		msg.m_len = m_len;
		update(msg, getNetAddress(sender.sin_addr, m_len));

		
		/*printf("Received UDP packet from IP address: >%s/%d<, port: %d\n", sender_ip_str, m_len, ntohs(sender.sin_port));
		printf("%s/%d\t", inet_ntoa(msg.ip), msg.m_len);
		printf("d = %u\t", msg.dist);
	 	//printf("%ld-byte message\t", datagram_len);
		//printf("mask len: %d\n", (int)m_len );
		printf("\n---------------------------------------\n");
	*/
	
	} 
	while(tv.tv_sec != 0 || tv.tv_usec != 0);
//		fflush(stdout);
}