CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

CSRC=transport.c utils.c wrappers.c window.c send.c receive.c

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
