// Przemysław Joniak, 282751

#include "router.h"

std::vector<neigh> dvct;
std::vector<struct in_addr> brdcsts;

int main() {
	readConfig();
	printDistVecotr();	
	send();
/*  
	//char cidr[] = "192.168.1.34/24";	
	struct in_addr ip, mask, brdcst;
	ip     = getIp(cidr);
	mask   = getMask(cidr);
	brdcst = getBroadcast(ip, mask);
	printf("ip=(%s)\n",   inet_ntoa(ip) );
	printf("mask=(%s)\n", inet_ntoa(mask) );
	printf("brdcs=(%s)\n",inet_ntoa(brdcst));
*/
	return 0;
}