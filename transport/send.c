#include "transport.h"
#include "wrappers.h"

void init_socket_send(int port) {
  sockfd_send = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero (&server_address_send, sizeof(server_address_send));
	server_address_send.sin_family      = AF_INET;
	server_address_send.sin_port        = htons(port);
	inet_pton(AF_INET, SERVER_IP, &server_address_send.sin_addr);
}

void send_request(int segment_number, char *datagram_len_str) {
  char message[60];
  char start_byte_str[10];
  sprintf(start_byte_str, "%d", segment_number*DATAGRAM_LEN);
  strcpy(message, "GET ");
  strcat(message, start_byte_str);
  strcat(message, " ");
  strcat(message, datagram_len_str);
  strcat(message, "\n");

  ssize_t message_len = strlen(message);
  Sendto(sockfd_send, message, message_len, 0, (struct sockaddr*) &server_address_send, sizeof(server_address_send));

}
