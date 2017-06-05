// Przemysław Joniak, 282751

#include "httpHeader.h"
#include "server.h"

bool dirExists(const std::string dir);

int main(int argc, char *argv[]) {

   if(argc != 3 || !dirExists(argv[2]) ) ERROR("Usage: ./httpserver port directory");

   int PORT = atoi(argv[1]);
   std::string dir  = argv[2];

   std::cout << "Listening on port: " << PORT << ". Direcotry: " << dir << "\n";

   Server srv(PORT, dir);
   while (1) srv.receive();

  return 0;
}


bool dirExists(const std::string dir) {
  struct stat sb;
  return (stat(dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
}
