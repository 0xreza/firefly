//server_sample.cpp <r68karimi[at]gmail.com>

#include "firefly.h"

#define MESSAGE_SIZE 1024

int main(int argc, char *argv[]){
    
    if (argc < 2){
        printf("[ERROR] correct usage: ./server port_number\n");
        exit(1);
    }

    firefly event_loop(atoi(argv[1]), MESSAGE_SIZE);
    event_loop.fire_event_loop();
    return 0;
}

int count = 0;
int firefly::on_read(char *buffer){
    count++;
    return 1;
}
int firefly::on_connection_close(int fd){
    printf("Connetion on descriptor %d is closed! -- %d\n", fd, count);
    return 1;
}