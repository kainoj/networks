// Przemysław Joniak 282751

#include "transport.h"
#include "wrappers.h"

const char *SERVER_IP = "156.17.4.30";

int main(int argc, char *argv[]) {
  if(argc != 4) ERROR("Usage: ./transport-* port output-file bytes");

  Port = atoi(argv[1]);
  strcpy(FileName, argv[2]);
  TotalDataSize = atoi(argv[3]);
  pFile = FOpen(FileName, "wb");

  char response_msg[60];
  int i, n = TotalDataSize / (WIN_SIZE*DATAGRAM_LEN);

  init_socket(Port);

  for(i=0; i < n; i++) {
    //printf("%.2f%% done\n", 100.0*i/n );
    byte_lower_bound = i*WIN_SIZE*DATAGRAM_LEN;
    sprintf(response_msg, "DATA %d %d\n", i*DATAGRAM_LEN, DATAGRAM_LEN);
    slideWindow(i*WIN_SIZE*DATAGRAM_LEN);
    do {
      send_request( WIN_SIZE);
      receive();
    } while( rcvd < WIN_SIZE );
    winToFile(WIN_SIZE);
  }

  // Window crumbs, eg when file len isnt divisible by DATAGRAM_LEN
  int last_byte = i*DATAGRAM_LEN*WIN_SIZE;
  int left_bytes = TotalDataSize - last_byte;
  int left_datagrams = left_bytes/DATAGRAM_LEN;
  left_datagrams = winCrumbs(last_byte, left_bytes, left_datagrams);

  rcvd = 0;
  if(left_datagrams){
    do {
      send_request(left_datagrams);
      receive();
    } while(rcvd < left_datagrams);
    winToFile(left_datagrams);
  }
  fclose(pFile);
  return 0;
}
