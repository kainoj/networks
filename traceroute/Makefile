CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

CSRC=comparehdrs.c err.c icmp.c print_response.c receive.c send.c traceroute.c

COBJ=$(CSRC:.c=.o)

traceroute: $(COBJ)
	$(CC) $(CFLAGS) $? -o $@

$(COBJ): $(CSRC)
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	rm -f *.o

distclean:
	rm -f *.o
	rm -f traceroute