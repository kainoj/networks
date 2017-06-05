// Przemysław Joniak, 282751

#include "httpHeader.h"

httpHeader::httpHeader(std::string header, std::string dir) {
  filesDir = dir;
  parseHttpRequest(header);
  content_type = getContentType();
  status = getStatusCode();
  composeResponse();
}

httpHeader::httpHeader(char *buff, std::string dir):
  httpHeader(std::string(buff), dir)
  {}

std::string httpHeader::getNextWord(std::string str, std::size_t fstWordPos, std::size_t wordLen) {
  std::size_t i = 1;
  while(str[fstWordPos+wordLen+i] != ' ' && str[fstWordPos+wordLen+i] != '\r') i++;
  return std::string(str, fstWordPos+wordLen+1, i-1);;
}


void httpHeader::parseHttpRequest(std::string header) {

  std::size_t pos;
  method = getNextWord(header, -1, 0); // returns first word in a string

//   #define FIND(pos, str, what)  if( ((pos) = (str).find(what)) == std::string::npos ) ERROR("error while parsing string");

  if( (pos = header.find(method)) != std::string::npos )
    resource = getNextWord(header, pos, method.length());

  if( (pos = header.find("Host: ")) != std::string::npos )
    host = getNextWord(header, pos, 5);

  if( (pos = header.find("Connection: ")) != std::string::npos)
    connection = getNextWord(header, pos, 11);

  pos = host.find(":");
  pageDir = (pos == std::string::npos)  ? host : std::string(host, 0, pos );

  filePath = filesDir+"/"+pageDir + resource;

  // std::cout << "host = " << host <<  "\nfilesDir = " << filesDir << "\n"<< "pageDir = " << pageDir << "\nresource: " << resource << "\n";
  // std::cout << "fPath = " << filePath << "\n";
}


char* httpHeader::getResponse() const {
  return response;
}

std::size_t httpHeader::getResponseLen() const {
  return responseLen;
}

bool httpHeader::isConnectionClosed() const {
  return connection == "Closed";
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
  if( resource.find("../") != std::string::npos )  return 403;
  if( resource == "/" || (resource.find(".") == std::string::npos && dirExists(filePath))  ) return 301;
  if( fileExists(filePath) ) return 200;
    else return 404;
  return 500;
}


std::string httpHeader::getErrorMsg() {
  std::string fst = "<!doctype html><html><head><title>Error</title></head><body><h2>Error: ";
  return fst+statusCodes.at(status) + "</h2></body></html>";
}


std::size_t httpHeader::readFileContent() {
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
  fileContent = (char*) malloc (sizeof(char)*lSize);
  if (fileContent == NULL) ERROR("open file: malloc error");

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
  std::cout << "File path: \t"  << filePath  << "\n";
  std::cout << "Status code:\t" << status    << "\n";
  // std::cout << "Files dir:  \t" << filesDir  << "\n";
  // std::cout << "Page dir:   \t" << pageDir   << "\n";
  // std::cout << "\nResponse: \n" << response  << "\n";
  std::cout << "---------------------------\n\n";
}

void httpHeader::printBriefInfo() {
  std::cout << method << " " << resource << "\n";
  std::cout << "Connection: " << connection << '\n';
  std::cout << "Status: " << status << "\n\n";
}


bool httpHeader::dirExists(const std::string dir) {
  struct stat sb;
  return (stat(dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
}

bool httpHeader::fileExists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
