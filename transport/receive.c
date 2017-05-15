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
        size_t response_msg_len = strlen(response_msg);
        memcpy(response_hdr, buffer, response_msg_len);
        //printf("msg1:\t >%s<", response_msg);
        //printf("msg2:\t >%s<", response_hdr);
        response_hdr[response_msg_len] = '\0';
        if( !strcmp(response_hdr, response_msg)) {
          fwrite(buffer+response_msg_len, sizeof(char), datagram_len, pFile);
          received = true;
        }
      }
    //  char sender_ip_str[20];
  	// 	inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
  	//	printf ("Received UDP packet from IP address: %s, port: %d\n", sender_ip_str, ntohs(sender.sin_port));
    }
  } while(received == false && (tv.tv_sec != 0 || tv.tv_usec != 0));

  return received;
}
