CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

CSRC=httpserver.cpp wrappers.cpp  httpHeader.cpp httpHeaderResponse.cpp server.cpp

COBJ=$(CSRC:.cpp=.o)

httpserver: $(COBJ) httpHeader.h
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC) httpHeader.h
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f httpserver
