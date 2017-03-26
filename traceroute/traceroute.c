#include "traceroute.h"

// wrzuc do .c:
void print_as_bytes (unsigned char* buff, ssize_t length)
{
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);	
}

void print_as_bytes_ip_data (unsigned char* buff, ssize_t length)
{
	if(*buff == 0) printf("type: echo replay\n");
	if(*buff == 11) printf("type: time exceeded\n");
	print_as_bytes(buff, length);	
}
/////////


struct icmphdr icmp_header[3];

int main() {
	// Inicjacja
	PID = getppid();
	//int SEQ = 1;

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 	{
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	for(int i=0; i<3; i++) {
		init_icmp_header(&icmp_header[i]);
		//icmp_send(sockfd, &icmp_header[i], "212.77.98.9", 42 );
	}

	

	
	
	
	//int ready;
	
	for(int ttl = 1; ttl<=TTL; ttl++) {
		getchar();

		printf("\n> Wysyłam %d-ta (jeszcze nie) paczke pakietow\n", ttl);

		// Wysyłanie
		for(int seq=0; seq<PACKETS; seq++) {
			update_icmp_header(&icmp_header[seq], 3*ttl+seq); // potem zmien - ma byc seq!!
			icmp_send(sockfd, icmp_header, "212.77.98.9", ttl);
		}

		fd_set descriptors;
		FD_ZERO (&descriptors);
		FD_SET (sockfd, &descriptors);
		struct timeval tv; tv.tv_sec = TIMEOUT; tv.tv_usec = 0;

		for(int rec=0; rec<PACKETS; rec++) {
			int ready = select (sockfd+1, &descriptors, NULL, NULL, &tv);

			printf("time left: %ld.%ld\n", tv.tv_sec, tv.tv_usec);

			if(ready < 0) {
				fprintf(stderr, "select: error recievning sockets\n"); return EXIT_FAILURE;	}
			else if(ready==0) { printf("TIMEOUT\n");	}
			else {
				//////
				//// Odbieranie
				/////

				struct sockaddr_in  sender;	
				socklen_t           sender_len = sizeof(sender);
				u_int8_t            buffer[IP_MAXPACKET];

				//printf("%d packets recieved\n", ready);
				for(int i=0; i< ready; i++) {
					ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
					if (packet_len < 0) {
						fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
						return EXIT_FAILURE;
					}

					char sender_ip_str[20]; 
					inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
					printf ("Received IP packet with ICMP content from: %s\n", sender_ip_str);

					struct iphdr* 		ip_header = (struct iphdr*) buffer;
					ssize_t				ip_header_len = 4 * ip_header->ihl;

				/*	printf ("IP header: "); 
					print_as_bytes (buffer, ip_header_len);
					printf("\n");

					printf ("IP data:   ");
					print_as_bytes_ip_data (buffer + ip_header_len, packet_len - ip_header_len);
					printf("\n\n");*/
					
				}
			}
		}
	}
	return 0;
}