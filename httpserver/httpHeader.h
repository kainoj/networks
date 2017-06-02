#ifndef HTTPHEADER
#define HTTPHEADER

#include <string>
#include <iostream>
#include <map>

#define FIND(pos, str, what)  if( ((pos) = (str).find(what)) == std::string::npos ) ERROR("error while parsing string");

class httpHeader {
  std::string method;
  std::string host;
  std::string connection;
  std::size_t status;
  std::string content_type;
  std::size_t content_length;

  std::string resource;
  std::string filesDir;
  std::string pageDir;
  std::string response;

  public:
    httpHeader(char *buff, std::string dir);
    httpHeader(std::string header, std::string dir);
    std::string getResponse() const;
    void printInfo();

  private:
    std::string getNextWord(std::string str, std::size_t fstWordPos, std::size_t wordLen);
    void parseHttpRequest(std::string header);
    void composeResponse();
    std::string getContentType();
    std::size_t getStatusCode();
    std::string getErrorMsg();

  const std::map<int, std::string> statusCodes {
    {200, "200 OK"},
    {301, "301 Moved Permanently"},
    {403, "403 Forbidden"},
    {404, "404 Not Found"},
    {500, "500 Internal Server Error"},
    {501, "501 Not Implemented"}
  };

  std::map<std::string, std::string> contentTypes {
    {"txt",  "text/plain"},
    {"html", "text/html"},
    {"css",  "text/css"},
    {"jpg",  "image/jpeg"},
    {"jpeg", "image/jpeg"},
    {"png",  "image/png"},
    {"pdf",  "application/pdf"},
    {"other","application/octet-stream"}
  };

};

#endif
