// Przemysław Joniak, 282751

#include "httpHeader.h"
#include "wrappers.h"
#include "httpserver.h"

void httpHeader::composeResponse400() {
  content_type = contentTypes.at("html");
  std::string responseBody = getErrorMsg();
  responseStr += "Content-Type: text/html\r\n";
  responseStr += "Content-Length: " + std::to_string(responseBody.length()*sizeof(char)) + "\r\n\r\n";
  responseStr += responseBody;
  responseStr += "\r\n\r\n";

  responseLen = responseStr.length()*sizeof(char);
  response = new char[responseLen];
  memcpy(response, responseStr.c_str(), responseLen);
}



void httpHeader::composeResponse300() {
  if(resource == "/")
    responseStr += "Location: http://" + host + DefaultFile;
  else
    responseStr += "Location: http://" + host + resource + DefaultFile;
  std::cout << "#30X responseStr = " << responseStr << "\n--\n";
  responseStr += "\r\n\r\n";

  responseLen = responseStr.length()*sizeof(char);
  response = new char[responseLen];
  memcpy(response, responseStr.c_str(), responseLen);
}



void httpHeader::composeResponse200() {
  std::size_t fileLen = readFileContent(); // in Bytes
  responseStr += "Content-Type: " + getContentType() + "\r\n";
  responseStr += "Content-Length: " + std::to_string(fileLen) + "\r\n\r\n";

  responseLen = responseStr.length()*sizeof(char);// + fileLen;
  response = new char[responseLen+fileLen];
  memcpy(response, responseStr.c_str(), responseLen);
  memcpy(response+responseLen, fileContent, fileLen);

  responseLen += fileLen;
}




void httpHeader::composeResponse() {
  responseStr = "HTTP/1.1 " + statusCodes.at(status) + "\r\n";
  responseStr += "Server: kainoj2k17\r\n";
  switch(status) {
    case 200:
      composeResponse200();
      break;
    case 301:
      composeResponse300();
      break;
    default:
      composeResponse400();
    break;
  }
}
