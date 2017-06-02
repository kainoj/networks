// Przemysław Joniak, 282751

#include "httpserver.h"

bool dirExists(const std::string dir) {
  struct stat sb;
  return (stat(dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
}

bool fileExists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
