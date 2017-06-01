#include "httpHeader.h"
#include "wrappers.h"




httpHeader::httpHeader(std::string header) {
  parseHttpRequest(header);

  printInfo();
}

httpHeader::httpHeader(char *buff) {
  httpHeader(std::string(buff));
}

std::string httpHeader::getNextWord(std::string str, std::size_t fstWordPos, std::size_t wordLen) {
  std::size_t i = 1;
  while(str[fstWordPos+wordLen+i] != ' ' && str[fstWordPos+wordLen+i] != '\n') i++;
  // line in http header is terminated with '\r\n'
  if(str[fstWordPos+wordLen+i-1] == '\r') i--;
  return std::string(str, fstWordPos+wordLen+1, i-1);;
}

void httpHeader::parseHttpRequest(std::string header) {
  std::size_t pos;
  method = getNextWord(header, -1, 0); // returns first word in a string

  FIND(pos, header, method);
  resource = getNextWord(header, pos, method.length());

  FIND(pos, header, "Host:");
  host = getNextWord(header, pos, 5);

  FIND(pos, header, "Connection:");
  connection = getNextWord(header, pos, 11);
}

void httpHeader::printInfo() {
  std::cout << "Method: \t"    << method     << "\n";
  std::cout << "Resource: \t"  << resource   << "\n";
  std::cout << "Host:   \t"    << host       << "\n";
  std::cout << "Connection:\t" << connection << "\n";
}
