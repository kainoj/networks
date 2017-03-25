#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <assert.h>
#include <unistd.h> // PID

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

int main() {
	int PID = getppid();

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) 	{
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	struct icmphdr icmp_header;
	icmp_header.type = ICMP_ECHO;
	icmp_header.code = 0;
	icmp_header.un.echo.id = 23;
	icmp_header.un.echo.sequence = PID;
	icmp_header.checksum = 0;
	icmp_header.checksum = compute_icmp_checksum (
	(u_int16_t*)&icmp_header, sizeof(icmp_header));	

	struct sockaddr_in recipient	;
	bzero (&recipient, sizeof(recipient));
	recipient.sin_family = AF_INET;
	inet_pton(AF_INET, "212.77.98.9", &recipient.sin_addr); // wp.pl

	int ttl = 42;
	setsockopt (sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

	ssize_t bytes_sent = sendto (
		 sockfd,
		 &icmp_header,
		 sizeof(icmp_header),
		 0,
		 (struct sockaddr*)&recipient,
		 sizeof(recipient)
	);
	
	printf("Moj pid: %d\n", PID );

	return EXIT_SUCCESS;
}