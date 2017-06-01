#pragma once

#include <string>
#include <iostream>

#define FIND(pos, str, what)  if( ((pos) = (str).find(what)) == std::string::npos ) ERROR("error while parsing string");

class httpHeader {
  std::string method;
  std::string host;
  std::string connection;
  std::string status;
  std::string content_type;
  std::string content_length;
  std::string resource;

  public:
    httpHeader(char *buff);
    httpHeader(std::string header);
    void printInfo();
  private:
    std::string getNextWord(std::string str, std::size_t fstWordPos, std::size_t wordLen);
    void parseHttpRequest(std::string header);
};
