// Przemysław Joniak, 282751

#include "traceroute.h"

void Error(char *msg) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errno)); 
	exit(EXIT_FAILURE);
}