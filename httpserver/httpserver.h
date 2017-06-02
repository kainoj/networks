#ifndef HTTPSERVER
#define HTTPSERVER

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include <errno.h>


//int PORT;
//std::string DIR;

bool dirExists(std::string dir);
bool fileExists(const std::string& name);

#endif
