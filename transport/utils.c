#include "transport.h"

void Error(char *msg) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}
