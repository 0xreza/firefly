//server_sample.cpp <r68karimi[at]gmail.com>

#include "firefly.h"

int main(int argc, char *argv[]){
    
    if (argc < 2){
        printf("[ERROR] correct usage: ./server port_number\n");
        exit(1);
    }

    firefly event_loop(argv[1], 1024);
    event_loop.fire_event_loop();
    return 0;
}

int firefly::on_read(char *buffer){
    printf("data read: %s\n", buffer);
    return 1;
}