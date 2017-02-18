//client_sample.cpp <r68karimi[at]gmail.com>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <netdb.h>

#define MESSAGE_SIZE 1024

int main(int argc, char **argv) {
    
    char *hostname={'\0'};
    struct sockaddr_in sin;
    struct hostent *h;
    
    if (argc < 3){
        printf("Usage: ./client server_ip server_port\n");
        exit (1);
    }

    h = gethostbyname(argv[1]);
    if (!h) {
        fprintf(stderr, "Couldn't lookup %s: %s", hostname, hstrerror(h_errno));
        return 1;
    }
    if (h->h_addrtype != AF_INET) {
        fprintf(stderr, "No ipv6 support, sorry.");
        return 1;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    /* Connect to the remote host. */
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(argv[2]));
    sin.sin_addr = *(struct in_addr*)h->h_addr;

    while(1){
        if (connect(fd, (struct sockaddr*) &sin, sizeof(sin))) {
          //--- waiting for server
        } else {
            break;
        }
    }

    printf("Connected to the server!\n");

    char buffer[MESSAGE_SIZE];
    for(int i=0; i<1000000; i++){
      sprintf(buffer, "%d", i);
      printf("Sending message to the server! '%s'\n", buffer);
      send(fd, buffer, MESSAGE_SIZE, 0);
    }

    close(fd);
    return 0;
}
