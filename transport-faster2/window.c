// Przemysław Joniak 282751

#include "transport.h"
#include "wrappers.h"

void slideWindow(int start_win_byte) {
  rcvd = 0;
  for(int i=0; i<WIN_SIZE; i++) {
    window[i].received = false;
    window[i].start_byte = start_win_byte+i*DATAGRAM_LEN;
    window[i].data_length = DATAGRAM_LEN;
  }
}

void storeDatagram(int start_byte, char *buffer) {
  for(int i=0; i<WIN_SIZE; i++) {
    if(window[i].start_byte == start_byte && window[i].received == false) {
      memcpy(window[i].data, buffer, DATAGRAM_LEN);
      rcvd++;
      window[i].received = true;
    }
  }
}

void winToFile(int win_size) {
  for(int i=0; i<win_size; i++) {
    FWrite(window[i].data, sizeof(char), window[i].data_length, pFile);
  }
}

int winCrumbs(int last_byte, int left_bytes, int left_datagrams) {

  for(int j=0; j<WIN_SIZE; j++) {
    window[j].received = true;
    strcpy(window[j].data, "");
  }
  int i;
  for(i=0; i<left_datagrams; i++) {
    window[i].received = false;
    window[i].start_byte = last_byte+i*DATAGRAM_LEN;
    window[i].data_length = DATAGRAM_LEN;
  }
  if( left_bytes% DATAGRAM_LEN ) {
    window[i].received = false;
    window[i].start_byte = last_byte+i*DATAGRAM_LEN;
    window[i].data_length = left_bytes % DATAGRAM_LEN;
    left_datagrams++;
  }
  return left_datagrams;
}
