CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

CSRC=httpserver.cpp wrappers.cpp  httpHeader.cpp

COBJ=$(CSRC:.cpp=.o)

httpserver: $(COBJ) httpserver.h
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC) httpserver.h
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f httpserver
