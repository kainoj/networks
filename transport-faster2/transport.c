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

  init_socket(Port);

  int i, n = TotalDataSize / (WIN_SIZE*DATAGRAM_LEN);

  printf("Okno ma rozmiar: %d\npojedynczy datagram %d B\nbajtow w oknie %d", WIN_SIZE,  DATAGRAM_LEN, WIN_SIZE*DATAGRAM_LEN);
  printf("TotalDataSize = %d\n", TotalDataSize );
  printf("przesuwow bedzie %d\n", n);

  for(i=0; i < n; i++) {
    printf("przesuw nr %d\n", i);
    printf("bajty:  %d -  %d\n",i*WIN_SIZE*DATAGRAM_LEN, (i+1)*WIN_SIZE*DATAGRAM_LEN -1 );
    printf("%.2f%% done\n", 100.0*i/n );

    byte_lower_bound = i*WIN_SIZE*DATAGRAM_LEN;
    sprintf(response_msg, "DATA %d %d\n", i*DATAGRAM_LEN, DATAGRAM_LEN);
    slideWindow(i*WIN_SIZE*DATAGRAM_LEN);
    do {
      send_request(i*WIN_SIZE*DATAGRAM_LEN, DATAGRAM_LEN, WIN_SIZE);
      receive(response_msg, DATAGRAM_LEN);
    } while( rcvd < WIN_SIZE );
    winToFile(WIN_SIZE);
  }

  // If file length is not divisible by DATAGRAM_LEN:
/*  int left_datagram_len = TotalDataSize % DATAGRAM_LEN;
  if( left_datagram_len ) {
    sprintf(request_msg,   "GET %d %d\n", i*DATAGRAM_LEN, left_datagram_len);
    sprintf(response_msg, "DATA %d %d\n", i*DATAGRAM_LEN, left_datagram_len);
    do {
      //send_request(request_msg);
    } while( receive(response_msg, left_datagram_len) == false );
  }
  printf("100.00%% DONE!\n");
  */
  fclose(pFile);
  return 0;
}
