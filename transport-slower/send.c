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

void send_request(char *request_msg) {
  ssize_t message_len = strlen(request_msg);
  Sendto(sockfd, request_msg, message_len, 0, (struct sockaddr*) &server_address, sizeof(server_address));
}
