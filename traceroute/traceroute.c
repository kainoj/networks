// Przemysław Joniak, 282751

#include "traceroute.h"

int main(int argc, char *argv[]) {
	if(argc !=2) { printf("Usage:\n#>./traceroute ip_addr\n"); return -1; }
	if(is_valid_ip_addr(argv[1]) ==  false) { printf("IP address is not valid"); return -1; }

	PID = getppid();
	is_echo_reply = is_timeout = false;

	struct icmphdr icmp_header[PACKETS];
	reply replies[PACKETS];
	int packets_received = 0;

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 	{
		Error("socket()");
	}	

	for(int i=0; i<PACKETS; i++) {
		init_icmp_header(&icmp_header[i]);
	}
		
	for(int ttl = 1; ttl<=TTL; ttl++) {
		// Inicjowanie pakietów
		for(int seq=0; seq<PACKETS; seq++) {
			update_icmp_header(&icmp_header[seq], 3*ttl+seq-2); // numeracja od 1
			replies[seq].time = -1;
		}
		// Wysyłanie - 3 pakiety tuż po sobie
		for(int seq=0; seq<PACKETS; seq++) {
			icmp_send(sockfd, &icmp_header[seq], argv[1], ttl); // ii
		}

		if( gettimeofday(&send_time, NULL) < 0 ) Error("gettimeofday()");
		printf("\t\tSend time: %ld\n", send_time.tv_usec);
		// Odbieranie
		packets_received = receive(&sockfd, icmp_header, replies);

		// Wyświetlanie
		print_response(ttl, packets_received, replies);

		if(is_echo_reply) return 0;
	}
	return 0;
}