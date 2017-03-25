#include "traceroute.h"

struct icmphdr icmp_header[3];

int main() {
	// Inicjacja
	PID = getppid();
	int SEQ = 1;

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 	{
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	for(int i=0; i<3; i++) {
		init_icmp_header(&icmp_header[i]);
		//icmp_send(sockfd, &icmp_header[i], "212.77.98.9", 42 );
	}

	// Odbieranie
	struct sockaddr_in  sender;	
	socklen_t           sender_len = sizeof(sender);
	u_int8_t            buffer[IP_MAXPACKET];

	fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (sockfd, &descriptors);
	struct timeval tv; tv.tv_sec = TIMEOUT; tv.tv_usec = 0;
	int ready;

	for(int ttl = 1; ttl<=TTL; ttl++) {
		printf("Wysyłam %d-ta paczke pakietow\n..", ttl);

		
		update_icmp_header(icmp_header, PID);
		

	//	printf("po");
		icmp_send(sockfd, icmp_header, "212.77.98.9", ttl);
		ready = select (sockfd+1, &descriptors, NULL, NULL, &tv);

		if(ready < 0) {
			fprintf(stderr, "select: error recievning sockets\n");
			return EXIT_FAILURE;
		}
		else if(ready==0) {
			printf("TIMEOUT\n");
		}
		else {
			printf("OK");


		}
	}
	return 0;
}