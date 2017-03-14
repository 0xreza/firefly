// server_sample.cpp <r68karimi[at]gmail.com>

#include <thread>
#include "firefly.h"

#define MESSAGE_SIZE 1024

using namespace std;

unsigned long count = 0;

void task1() {
  while (1) {
    // printf("count: %-40ld\n", count);
    sleep(1);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("[ERROR] correct usage: ./server port_number\n");
    exit(1);
  }
  thread t1(task1);
  firefly event_loop(atoi(argv[1]), MESSAGE_SIZE);
  event_loop.fire_event_loop();
  return 0;
}

int firefly::on_read(char* buffer, int len) {
  count += len;
  // printf("%d\n", count);
  return 1;
}
int firefly::on_connection_close(int fd) {
  printf("Connetion on descriptor %d is closed! -- %ld\n", fd, (long)count);
  return 1;
}