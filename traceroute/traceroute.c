#include "traceroute.h"


int main() {
	PID = getppid();

	struct icmphdr icmp_header[3];

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 	{
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	for(int i=0; i<3; i++) {
		init_icmp_header(&icmp_header[i]);
	}
		
	for(int ttl = 1; ttl<=TTL; ttl++) {
		//getchar();
		printf("\n> Wysyłam %d-ta paczke pakietow\n", ttl);

		// Wysyłanie
		for(int seq=0; seq<PACKETS; seq++) {
			update_icmp_header(&icmp_header[seq], 3*ttl+seq-2); // numeracja od 1
			icmp_send(sockfd, &icmp_header[seq], "212.77.98.9", ttl); // ii
		}
	
		// Odbieranie
		receive(&sockfd, icmp_header);
	}
	return 0;
}