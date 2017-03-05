CC= g++
BINDIR= bin/
LIB=lib/
CFLAGS= -std=c++11 -Wall -O3 -I$(LIB)
LDFLAGS= 
SRCFOLDER=sample/
PROGRAMS= server_sample client_sample

all: $(PROGRAMS)

server_sample:
	$(CC) $(CFLAGS) -o $(BINDIR)server $(SRCFOLDER)server_sample.cpp $(LDFLAGS)

client_sample:
	$(CC) $(CFLAGS) -o $(BINDIR)client $(SRCFOLDER)client_sample.cpp $(LDFLAGS)
