CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

CSRC=utils_ip.cpp utils_io.cpp router.cpp send.cpp receive.cpp

COBJ=$(CSRC:.cpp=.o)

router: $(COBJ) router.h
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC) router.h
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f router