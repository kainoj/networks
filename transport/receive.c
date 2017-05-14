#include "transport.h"
#include "wrappers.h"

void init_socket_recv(int port) {
  sockfd_recv = socket(AF_INET, SOCK_DGRAM, 0);
	bzero (&server_address_recv, sizeof(server_address_recv));
	server_address_recv.sin_family      = AF_INET;
	server_address_recv.sin_port        = htons(port);
	server_address_recv.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(sockfd_recv, (struct sockaddr*)&server_address_recv, sizeof(server_address_recv));
}

bool receive() {

  bool received = false;

  struct sockaddr_in sender;
  socklen_t          sender_len = sizeof(sender);
  char               buffer[IP_MAXPACKET+1];

  fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (sockfd_recv, &descriptors);
  struct timeval tv = {TIMEOUT_SEC, TIMEOUT_USEC};

  ssize_t datagram_len;
	char sender_ip_str[20];
  do {
    int ready = select(sockfd_recv+1, &descriptors, NULL, NULL, &tv);
    printf("ready = %d\n", ready);

    if(ready>0) {
      datagram_len = recvfrom(sockfd_recv, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
    	inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
  		printf ("Received UDP packet from IP address: %s, port: %d\n", sender_ip_str, ntohs(sender.sin_port));
  		printf ("%ld-byte message: +%s+\n", datagram_len, buffer);
      received = true;
    }

  }
  while((tv.tv_sec != 0 || tv.tv_usec != 0) && received);
  return received;
}
