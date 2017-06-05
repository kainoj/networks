// Przemysław Joniak, 282751

#include "server.h"
#include "httpHeader.h"

Server::Server(int port, std::string dir) : port(port), dir(dir) {
  sockfd = Socket(AF_INET, SOCK_STREAM, 0);
  bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(port);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  Bind (sockfd, &server_address, sizeof(server_address));
  Listen (sockfd, 64);
}



void Server::receive() {
  conn_sockfd = Accept (sockfd, NULL, NULL);
  initSelect();
  do {
    if( Select(conn_sockfd+1, &descriptors, NULL, NULL, &tv) > 0 ) {
      int n = Recv(conn_sockfd, buffer, BUFFSIZE, 0);
      if( n > 0 ) {
        buffer[n] = 0;
        //printf("Received header: \n%s\n---------------\n", buffer );
        httpHeader hdr(buffer, dir);
        hdr.printBriefInfo();
        Send (conn_sockfd, (char *)hdr.getResponse(), hdr.getResponseLen(), 0);
        if(hdr.isConnectionClosed()) tv.tv_sec = tv.tv_usec = 0;
        //stv.tv_usec += 100000;
      }
    }
  } while(tv.tv_sec != 0 || tv.tv_usec != 0);
  Close (conn_sockfd);
}



void Server::initSelect() {
  FD_ZERO (&descriptors);
  FD_SET (conn_sockfd, &descriptors);
  tv = { TIMEOUT_SEC, TIMEOUT_USEC };
}
