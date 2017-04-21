#include "router.h"

struct in_addr getIp(char cidr[]) {	
	// Extract ip from CIDR notation
	char ip[15];
	int off = 3;
	size_t len = strlen(cidr);
	if(cidr[len-3] != '/') off = 2;
	strncpy(ip, cidr, len-off);
	ip[len-off]='\0';
	
	// And pack it into a struct
	struct in_addr IP;
	inet_aton(ip, &IP);
	return IP;
}

struct in_addr getMask(char cidr[]) {
	// Extract mask length form CIDR
	uint32_t m = 0;
	size_t len = strlen(cidr);
	if(cidr[len-3] == '/')
		m = 10*( (int) cidr[len-2]-'0') + (int) cidr[len-1]-'0';
	else m = (int) cidr[len-1]-'0';
	
	// Convet to binary
	m = ((1 << m)-1);
	// Pack into a struct
	struct in_addr mask;
	mask.s_addr = m;
	return mask;
}

struct in_addr getBroadcast(struct in_addr ip, struct in_addr mask) {
	struct in_addr brdcst;
	brdcst.s_addr =  ip.s_addr | ~mask.s_addr;
	return brdcst;
}