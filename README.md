# firefly
Firefly: A Lightweight Asynchronous IO Library

firefly is built on the top of epoll as an abstraction layer. 
It is aimed to be as light, efficient and fast as possible. So we avoid making it tooooo complex. 
Firefly is here to make the life easier.

![firefly-eventloop](https://sugoiinu.files.wordpress.com/2012/09/firefly-1.jpg?w=610&h=405 "firefly")

**Features:**

- [x] built on top of 'epoll', most efficient system call for async io.
- [x] extremely easy to use. make a firefly instance, define on_read function, firefly.loop(), and you're done!
- [x] it knows your message size, buffers messages on different file descriptors and calls on_read when it's ready.
- [x] on_connection_accept, on_connection_close methods are definable.
- [ ] supports threadpool and workerpool
- [x] add any other file description to the event loop, firefly takes care of them not only connections

 
 
***3-Step Usage:***
 
```c++
// 1. include the library
#include <firefly.h>

// 2. define on_read, on_connection_accept, on_connection_close methods
int firefly::on_read(char *buffer){
    printf("data read: %s\n", buffer);
    return 1;
}
int firefly::on_connection_accept(int fd, char* host, char* port){
    printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", fd, host, port);
    return 1;
}
int firefly::on_connection_close(int fd){
    printf("Connetion on descriptor %d is closed!\n", fd);
    return 1;
}

// 3. create an event loop instance in the main function
firefly event_loop(port, message_size);
event_loop.fire_event_loop();

// done! wasn't so simple? :)

```
---
\* *Firefly* is a work under process, published under Gnu Public License v3.0. Please feel free to use, contribute or sending me your valuable feedbacks. r68karimi [at] gmail [dot] com


