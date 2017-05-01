// Przemysław Joniak, 282751

#include "router.h"

void send() {
	for(size_t i=0; i<dvct.size(); i++) {
		for(size_t j=0; j<neigh_nets.size(); j++) {
			if( Sendto(i, j) == false ) {
				dvct[j].reachable = false;
			}
		}
	}
}

bool Sendto(size_t i, size_t j) {
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		exit(1); //return EXIT_FAILURE;
	}

	struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(PORT);
	inet_pton(AF_INET, inet_ntoa(getBroadcast(neigh_nets[j].ip, neigh_nets[j].m_len)), &server_address.sin_addr);

	int broadcastPermission = 1;
	setsockopt (sockfd, SOL_SOCKET, SO_BROADCAST,
					(void *)&broadcastPermission,
					sizeof(broadcastPermission));

	// Adjust data to network byte order
	ssize_t msg_len = sizeof(dvct[i].info), res;
	neigh_info msg = dvct[i].info;

	if(dvct[i].reachable) 
		msg.dist = htonl(msg.dist);
	else
		msg.dist = htonl(INF);

	res = sendto(sockfd, &msg, msg_len, 0, (struct sockaddr*) &server_address, sizeof(server_address));
	close (sockfd);
	return res == msg_len;
}
