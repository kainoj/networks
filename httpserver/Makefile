CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

CSRC=httpserver.cpp wrappers.cpp  httpHeader.cpp utils.cpp httpHeaderResponse.cpp

COBJ=$(CSRC:.cpp=.o)

httpserver: $(COBJ) httpserver.h httpHeader.h
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC) httpserver.h httpHeader.h
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f httpserver
