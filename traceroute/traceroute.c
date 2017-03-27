#include "traceroute.h"

int main() {
	PID = getppid();

	struct icmphdr icmp_header[PACKETS];
	reply replies[PACKETS];
	int packets_received = 0;

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 	{
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	for(int i=0; i<PACKETS; i++) {
		init_icmp_header(&icmp_header[i]);
	}
		
	for(int ttl = 1; ttl<=TTL; ttl++) {
		printf("\n> Wysyłam %d-ta paczke pakietow\n", ttl);
		// Inicjowanie pakietów
		for(int seq=0; seq<PACKETS; seq++) {
			update_icmp_header(&icmp_header[seq], 3*ttl+seq-2); // numeracja od 1
			replies[seq].time = -1;
		}

		// Wysyłanie - 3 pakiety tuż po sobie
		for(int seq=0; seq<PACKETS; seq++) {
			icmp_send(sockfd, &icmp_header[seq], "212.77.98.9", ttl); // ii
		}
	
		// Odbieranie
		packets_received = receive(&sockfd, icmp_header, replies);

		// Wyświetlanie
		print_response(ttl, packets_received, replies);
	}
	return 0;
}