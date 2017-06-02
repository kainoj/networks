// Przemysław Joniak, 282751

#include "httpHeader.h"
#include "wrappers.h"
#include "httpserver.h"

httpHeader::httpHeader(std::string header, std::string dir) {
  filesDir = dir;

  parseHttpRequest(header);
  content_type = getContentType();
  status = getStatusCode();
  printInfo();
}

httpHeader::httpHeader(char *buff, std::string dir) {
  httpHeader(std::string(buff), dir);
}


void httpHeader::composeResponse() {
  response = "HTTP/1.1 " + statusCodes.at(status) + "\r\n";
  response+= "Server: kainoj2k17\r\n";

  switch(status) {
    case 200: std::cout <<  "200 ToDO";
      break;
    case 301: std::cout <<  "300 ToDO";
      break;
    default:
      std::cout <<  ">400 ToDO";
    break;
  }


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

  pos = host.find(":");
  pageDir = (pos == std::string::npos)  ? host : std::string(host, 0, pos );
}


std::string httpHeader::getResponse() const {
  return response;
}


std::string httpHeader::getContentType() {
  int dotPos=resource.length()-1;
  while(dotPos>=0 && resource[dotPos] != '.') dotPos--;
  std::string fileExtension(resource, dotPos+1, resource.length()-dotPos);
  if(contentTypes.find(fileExtension) == contentTypes.end())
    return contentTypes.at("other");
  return contentTypes.at(fileExtension);
}


std::size_t httpHeader::getStatusCode() {
  if( method != "GET") return 501;
  if( resource == "/") return 301;
  if( resource.find("../") != std::string::npos )   return 403;
  if( fileExists(filesDir+"/"+pageDir + resource) ) return 200;
    else return 404;
  return 500;
}


std::string httpHeader::getErrorMsg() {
  std::string fst = "<!doctype html><html><head><title>Error</title></head><body><h2>Error: ";
  return statusCodes.at(status) + "</h2></body></html>";
}






////////////////////    DEBUG    ////////////////////

void httpHeader::printInfo() {
  std::cout << "------- Header info -------" << '\n';
  std::cout << "Method: \t"    << method     << "\n";
  std::cout << "Resource: \t"  << resource   << "\n";
  std::cout << "Host:   \t"    << host       << "\n";
  std::cout << "Connection:\t" << connection << "\n";
  std::cout << "Content type:\t"<< content_type << "\n";
  std::cout << "Files dir:  \t" << filesDir  << "\n";
  std::cout << "Page dir:   \t" << pageDir   << "\n";
  std::cout << "Status code:\t" << status    << "\n";
  std::cout << "Response: \n"   << response  << "\n";
  std::cout << "---------------------------" << "\n";
}
