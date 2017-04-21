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
	// Extract mask length form CIDR
	size_t len = strlen(cidr);
	if(cidr[len-3] == '/')
		return  10*(cidr[len-2]-'0') + cidr[len-1]-'0';
	return cidr[len-1]-'0';
}

struct in_addr getBroadcast(struct in_addr ip, char mask_len) {
	struct in_addr brdcst;
	brdcst.s_addr =  ip.s_addr | ~((1 << mask_len)-1);
	return brdcst;
}