// Przemysław Joniak, 282751

#ifndef ROUTER
#define ROUTER

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <bool.h>

#define VECT_SIZE 32
int n;

struct in_addr getIp(char cidr[]);
struct in_addr getMask(char cidr[]);
struct in_addr getBroadcast(struct in_addr ip, struct in_addr m);

#endif
