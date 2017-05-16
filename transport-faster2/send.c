// Przemysław Joniak 282751

#include "transport.h"
#include "wrappers.h"

void init_socket(int port) {
  sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(port);
	inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
}

void send_request(int win_size) {
  char request_msg[60];

  for(int i=0; i<win_size; i++) {
    if(window[i].received == false) {
      //sprintf(request_msg,   "GET %d %d\n", start_byte+i*datagram_len, DATAGRAM_LEN);
      sprintf(request_msg,   "GET %d %d\n", window[i].start_byte, window[i].data_length);
      Sendto(sockfd, request_msg, strlen(request_msg), 0, (struct sockaddr*) &server_address, sizeof(server_address));
    }
  }

}
