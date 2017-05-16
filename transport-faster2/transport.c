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
      send_request( WIN_SIZE);
      receive();
    } while( rcvd < WIN_SIZE );
    winToFile(WIN_SIZE);
  }

  // window crumb
  int last_byte = i*DATAGRAM_LEN*WIN_SIZE;
  int left_bytes = TotalDataSize - last_byte;
  int left_datagrams = left_bytes/DATAGRAM_LEN;
  for(int j=0; j<WIN_SIZE; j++) {
    window[j].received = true;
    strcpy(window[j].data, "");
  }

  printf("pozostalo %d Bajtow \ndo podzialu na %d datagramow dl DATAGRAM_LEN\n", left_bytes, left_datagrams);
  printf("ostatni pakiet ma dl: %d\n", left_bytes % DATAGRAM_LEN);

  for(i=0; i<left_datagrams; i++) {
    window[i].received = false;
    window[i].start_byte = last_byte+i*DATAGRAM_LEN;
    window[i].data_length = DATAGRAM_LEN;
  }
  if( left_bytes% DATAGRAM_LEN ) {
    printf("zostal 1!!!!!\n" );
    window[i].received = false;
    window[i].start_byte = last_byte+i*DATAGRAM_LEN;
    window[i].data_length = left_bytes % DATAGRAM_LEN;
    left_datagrams++;
  }
  rcvd = 0;
  printf("left_datagrams = %d\n", left_datagrams );
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
