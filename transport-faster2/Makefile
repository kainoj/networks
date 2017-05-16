CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

CSRC=transport.c wrappers.c send.c receive.c window.c

COBJ=$(CSRC:.c=.o)

transport: $(COBJ)
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC)
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f transport
