// Przemysław Joniak, 282751

#include "httpserver.h"
#include "wrappers.h"
#include "httpHeader.h"

//using namespace std;

#define BUFFSIZE 10000000	// 10 MB
char buffer[BUFFSIZE+1];


int main(int argc, char *argv[]) {
  if(argc != 3 || !dirExists(argv[2]) ) ERROR("Usage: ./httpserver port directory");

  int PORT = atoi(argv[1]);
  std::string dir  = argv[2];
  std::cout << "Listening on port: " << PORT << ". Direcotry: " << dir << "\n";

  int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind (sockfd, &server_address, sizeof(server_address));
  Listen (sockfd, 64);

	while (1) {

		int conn_sockfd = Accept (sockfd, NULL, NULL);

		int n = Recv(conn_sockfd, buffer, BUFFSIZE, 0);
    if( n > 0 ) {
  		buffer[n] = 0;

      //printf("Received header: %s\n---------------\n", buffer );

      httpHeader hdr(buffer, dir);
      hdr.printInfo();

  		// Wysylanie odpowiedzi
  		Send (conn_sockfd, (char *)hdr.getResponse(), hdr.getResponseLen(), 0);
      }
		Close (conn_sockfd);
	}


  return 0;
}
