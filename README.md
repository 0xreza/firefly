# firefly
Firefly: A Lightweight Asynchronous IO Library

firefly is built on the top of epoll as an abstraction layer. 
It is aimed to be as light, efficient and fast as possible. So we avoid making it tooooo complex. 
Firefly is here to make the life easier.

![firefly-eventloop](https://sugoiinu.files.wordpress.com/2012/09/firefly-1.jpg?w=610&h=405 "firefly")

**Features:**

* built on top of 'epoll', most efficient system call for async io.
* extremely easy to use. make a firefly instance, define on_read function, firefly.loop(), and you're done!
* it knows your message size, buffers messages on different file descriptors and calls on_read when it's ready.
* on_accept, on_close functions can be defined.


**Coming features:**

* supporting threadpool and workerpool
* add any other file description to the event loop, firefly takes care of them not only connections
