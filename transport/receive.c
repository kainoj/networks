#include "transport.h"
#include "wrappers.h"

void init_socket_recv(int port) {
  sockfd_recv = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero (&server_address_recv, sizeof(server_address_recv));
	server_address_recv.sin_family      = AF_INET;
	server_address_recv.sin_port        = htons(port);
	server_address_recv.sin_addr.s_addr = htonl(INADDR_ANY);

  Bind(sockfd_recv, (struct sockaddr*)&server_address_recv, sizeof(server_address_recv));


}
