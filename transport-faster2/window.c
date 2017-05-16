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
