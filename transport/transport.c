#include "transport.h"
#include "wrappers.h"

const char *SERVER_IP = "156.17.4.30";

int main(int argc, char *argv[]) {
  if(argc != 4) ERROR("Usage: ./transport-* port output-file bytes");

  Port = atoi(argv[1]);
  strcpy(FileName, argv[2]);
  TotalDataSize = atoi(argv[3]);

  init_socket_send(Port);
  init_socket_recv(Port);

  char datagram_len_str[6];
  sprintf(datagram_len_str, "%d", DATAGRAM_LEN);

  int n = TotalDataSize / DATAGRAM_LEN;
  for(int i=0; i < n; i++) {
    printf("> %.2f%%\n", 100.0*i/n );
    do {
      printf("wysylam\n");
      send_request(i, datagram_len_str);
    } while( receive() == false );
  }
  return 0;
}
