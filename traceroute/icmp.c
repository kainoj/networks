// Przemysław Joniak, 282751

#include "traceroute.h"

u_int16_t compute_icmp_checksum (const void *buff, int length) {
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

void init_icmp_header(struct icmphdr *icmp_header) {
	icmp_header -> type = ICMP_ECHO;
	icmp_header -> code = 0;
	icmp_header -> un.echo.id = PID;
	icmp_header -> un.echo.sequence = 0;
	icmp_header -> checksum = 0;
	icmp_header -> checksum = compute_icmp_checksum (
		(u_int16_t*)icmp_header, sizeof(*icmp_header));
}

void update_icmp_header(struct icmphdr *icmp_header, u_int16_t echo_seq ) {
	icmp_header -> un.echo.sequence = echo_seq;
	icmp_header -> checksum = 0;
	icmp_header -> checksum = compute_icmp_checksum (
		(u_int16_t*)icmp_header, sizeof(*icmp_header));
}

bool is_valid_ip_addr(char *ip_addr) {
    struct sockaddr_in s;
    int res = inet_pton(AF_INET, ip_addr, &(s.sin_addr));
    return res != 0;
}

// Debug only
void print_icmp_header(struct icmphdr *icmp_header) {
	printf("> ICMP Header:\n");
	printf("ICMP type: \t%u\n", icmp_header->type);
	printf("ICMP code: \t%u\n", icmp_header->code);
	printf("ICMP id (pid): \t%u\n", icmp_header->un.echo.id);
	printf("ICMP checksum: \t%x\n", icmp_header->checksum);
	printf("ICMP sequence: \t%u\n", icmp_header->un.echo.sequence);
}
