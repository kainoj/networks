#include "transport.h"
#include "wrappers.h"

const char *SERVER_IP = "156.17.4.30";

int main(int argc, char *argv[]) {
  if(argc != 4) ERROR("Usage: ./transport-* port output-file bytes");

  Port = atoi(argv[1]);
  strcpy(FileName, argv[2]);
  TotalDataSize = atoi(argv[3]);

  pFile = fopen(FileName, "wb");

  init_socket(Port);

  char request_msg[60];
  char response_msg[60];

  int n = TotalDataSize / DATAGRAM_LEN;
  for(int i=0; i < n; i++) {
    printf("> %.2f%%\n", 100.0*i/n );
    sprintf(request_msg,   "GET %d %d\n", i*DATAGRAM_LEN, DATAGRAM_LEN);
    sprintf(response_msg, "DATA %d %d\n", i*DATAGRAM_LEN, DATAGRAM_LEN);

    do {
      printf(".");
      send_request(request_msg);
    } while( receive(response_msg) == false );
  }
  fclose(pFile);
  return 0;
}
