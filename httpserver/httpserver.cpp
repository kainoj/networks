// Przemysław Joniak, 282751

#include "httpserver.h"
#include "wrappers.h"
#include "httpHeader.h"

//using namespace std;

#define BUFFSIZE 10000000	// 10 MB
char buffer[BUFFSIZE+1];


int main(int argc, char *argv[]) {
  if(argc != 3) ERROR("Usage: ./httpserver port directory");

  PORT = atoi(argv[1]);
  DIR  = argv[2];
  std::cout << "Listening on port: " << PORT << ". Direcotry: " << DIR << "\n";

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
		int msglen = n;// < 20 ? n : 20;
		buffer[msglen] = 0;

    httpHeader hdr(buffer);

    //char reply_msg[1000];
  //  std::string qqq = buffer;
  //  std::cout << "msg: (" << qqq << ")\n";


	//	sprintf (reply_msg, "%d bytes read, first 20 bytes: ->%s<-", n, buffer);
	//	printf ("%d bytes read\nmsg:\n%s\n-----------------\n", n, buffer);

		// Wysylanie odpowiedzi
		// send(_,_,_,0) = write(_,_,_). Przy UDP bylo sendto, przy TCP jest send().
//		Send (conn_sockfd, reply_msg, strlen(reply_msg), 0);

		Close (conn_sockfd);
	}


  return 0;
}
