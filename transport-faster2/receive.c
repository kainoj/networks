// Przemysław Joniak 282751

#include "transport.h"
#include "wrappers.h"

bool receive(char *response_msg, int datagram_len) {
  bool received = false;
  int ready=0;
  struct sockaddr_in 	sender;
  socklen_t 			sender_len = sizeof(sender);
  char 			      buffer[IP_MAXPACKET+1];

  fd_set descriptors;
	FD_ZERO (&descriptors);
	FD_SET (sockfd, &descriptors);
	struct timeval tv = { TIMEOUT_SEC, TIMEOUT_USEC };
  
  do {
    ready = Select(sockfd+1, &descriptors, NULL, NULL, &tv);
    if(ready>0) {
      Recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);

      if(server_address.sin_port == sender.sin_port && server_address.sin_addr.s_addr == sender.sin_addr.s_addr) {
        char response_hdr[60];
        int start_byte_recv, datagram_len_recv;

        sscanf(buffer, "%*s %d %d", &start_byte_recv, &datagram_len_recv);
        sprintf(response_msg, "DATA %d %d\n", start_byte_recv, datagram_len_recv);

        size_t response_msg_len = strlen(response_msg);
        memcpy(response_hdr, buffer, response_msg_len);
        response_hdr[response_msg_len] = '\0';



        storeDatagram(start_byte_recv, datagram_len_recv, buffer+response_msg_len);
      }
    }
  } while(tv.tv_sec != 0 || tv.tv_usec != 0);

  return received;
}
