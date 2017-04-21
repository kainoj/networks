CC=g++
CFLAGS=-Wall -Wextra

CSRC=utilities.cpp router.cpp

COBJ=$(CSRC:.cpp=.o)

router: $(COBJ)
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC)
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f router