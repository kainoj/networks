// Przemysław Joniak, 282751

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

char getMaskLen(char cidr[]) {
	// Extract mask length foarm CIDR
	size_t len = strlen(cidr);
	if(cidr[len-3] == '/')
		return  10*(cidr[len-2]-'0') + cidr[len-1]-'0';
	return cidr[len-1]-'0';
}

struct in_addr getBroadcast(struct in_addr ip, char mask_len) {
	struct in_addr brdcst;
	uint32_t mask = htonl(~((1 << (32-mask_len))-1));
	brdcst.s_addr =  ip.s_addr | ~mask;
	return brdcst;
}

struct in_addr getNetAddress(struct in_addr ip, char mask_len) {
	struct in_addr net_addr;
	uint32_t mask = htonl(~((1 << (32-mask_len))-1));
	net_addr.s_addr =  ip.s_addr & mask;
	return net_addr;
}