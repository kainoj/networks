// Przemysław Joniak, 282751

#include "httpHeader.h"
#include "wrappers.h"
#include "httpserver.h"

httpHeader::httpHeader(std::string header, std::string dir) {
  filesDir = dir;

  parseHttpRequest(header);
  content_type = getContentType();
  status = getStatusCode();
  composeResponse();
  printInfo();
}

httpHeader::httpHeader(char *buff, std::string dir) {
  httpHeader(std::string(buff), dir);
}


void httpHeader::composeResponse() {
  response = "HTTP/1.1 " + statusCodes.at(status) + "\r\n";
  response+= "Server: kainoj2k17\r\n";
  switch(status) {
    case 200:
      response += "Content-Type: " + getContentType() + "\r\n";
      response += "Content-Length: " + std::to_string(readFileContent()) + "\r\n\r\n";
      response += fileContent; free(fileContent);
      break;
    case 301:
      response += "Location: http://" + host + DefaultFile;
      break;
    default:
      responseBody = getErrorMsg();
      response += "Content-Type: text/html\r\n";
      response += "Content-Length: " + std::to_string(sizeof(responseBody)) + "\r\n\r\n";
      response += responseBody;
    break;
  }
  response += "\r\n\r\n";
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

  filePath = filesDir+"/"+pageDir + resource;
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
  if( resource == "/" || resource == "" ) return 301;
  if( resource.find("../") != std::string::npos )   return 403;
  if( fileExists(filePath) ) return 200;
    else return 404;
  return 500;
}


std::string httpHeader::getErrorMsg() {
  std::string fst = "<!doctype html><html><head><title>Error</title></head><body><h2>Error: ";
  return fst+statusCodes.at(status) + "</h2></body></html>";
}


size_t httpHeader::readFileContent() {
// http://www.cplusplus.com/reference/cstdio/fread/

  FILE * pFile;
  size_t lSize;
  size_t result;

  pFile = fopen (filePath.c_str() , "rb" );
  if (pFile==NULL) ERROR(filePath.c_str());

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  fileContent = (char*) malloc (sizeof(char)*lSize);
  if (fileContent == NULL) ERROR("open file: memory error");

  // copy the file into the fileContent:
  result = fread (fileContent,1,lSize,pFile);
  if (result != lSize) ERROR("reading from file error");
  fclose (pFile);
  return lSize;
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
  std::cout << "File path: \t"  << filePath  << "\n";
  std::cout << "\nResponse: \n" << response  << "\n";
  std::cout << "---------------------------" << "\n";
}
