#include "traceroute.h"

bool compare(struct icmphdr *hdr, struct icmphdr *hdr2) {
	if(    
		   hdr -> type == hdr2 -> type
		&& hdr -> code == hdr2 -> code
		&& hdr -> un.echo.id == hdr2 -> un.echo.id
		&& hdr -> un.echo.sequence == hdr2 -> un.echo.sequence
		&& hdr -> checksum == hdr2 -> checksum
	) 
		return true;
	return false;
}

bool comparehdrs(struct icmphdr *sent_hdr, u_int8_t *buffer) {
	
	// Original IP header
	struct iphdr *ip_hdr = (struct iphdr*) buffer;

	// ICMP header (len = 8B)
	struct icmphdr *icmp_hdr = (struct icmphdr*) (buffer+ 4*(ip_hdr->ihl));
	
	if( icmp_hdr -> type == ICMP_TIME_EXCEEDED) {
		
		// 'Old' IP header (that was sent back)
		struct iphdr *old_ip_hdr = (struct iphdr*) (buffer+4*(ip_hdr->ihl)+sizeof(*icmp_hdr));

		// 'Old' ICMP header
		struct icmphdr *received_hdr = (struct icmphdr*) (buffer + 4*(ip_hdr->ihl) + sizeof(*icmp_hdr) + 4*(old_ip_hdr->ihl) );

		// Check if received ICMP header matches one of the previously sent
		for(int i=0; i<PACKETS; i++) {
			if(compare(received_hdr, &sent_hdr[i]))
				return true;
		}
	}

	if( icmp_hdr -> type == ICMP_ECHOREPLY) {
		for(int i=0; i<PACKETS; i++) {
			if(icmp_hdr -> un.echo.id == sent_hdr[i].un.echo.id
			   && icmp_hdr -> un.echo.sequence == sent_hdr[i].un.echo.sequence) {
				//printf(">>>>>>>>>Dostalem echoreply\n");
				return true;
			}
		}
	}
	return false;
}

