CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

CSRC=utilities.c router.c

COBJ=$(CSRC:.c=.o)

router: $(COBJ)
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC)
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f router