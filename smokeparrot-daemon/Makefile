PROGRAM = smokeparrot
CC = gcc

WARNINGS = -Wall -Wextra -Wformat -Wformat-security -Werror=format-security
HARDENING = -fstack-protector -D_FORTIFY_SOURCE=2 -pie -fPIE --param ssp-buffer-size=4 
DEFS = --std=c99 -pthread -D_REENTRANT -O1
FTM = -D_GNU_SOURCE
CFLAGS = $(DEFS) $(FTM) $(HARDENING) $(WARNINGS)

LDLIBS = -lmicrohttpd
LDFLAGS = -Wl,-z,relro -Wl,-z,now

objects = src/smokeparrot.o src/SP_http_response.o

all: $(PROGRAM)

$(PROGRAM) : $(objects)
	$(CC) $(LDFLAGS) -o bin/smokeparrot $(objects) $(LDLIBS)

smokeparrot.o : src/smokeparrot.o
	$(CC) $(CFLAGS) -c src/smokeparrot.c
SP_http_response.o : src/SP_http_response.o
	$(CC) $(CFLAGS) -c src/SP_http_response.c


clean :
	rm $(objects)

dist-clean:
	rm bin/smokeparrot
