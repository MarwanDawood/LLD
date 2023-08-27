## OS Development Using Linux Kernel tutorial
* This project is forked from `rockytriton/LLD:main`
* Code for https://www.youtube.com/playlist?list=PLVxiWMqQvhg8ZisiOBLAVkhLOYCkzTst0

Quoting from https://stackoverflow.com/questions/3784389/difference-between-api-and-abi
### API: Application Program Interface
This is the set of public types/variables/functions that you expose from your application/library.

In C/C++ this is what you expose in the header files that you ship with the application.
### ABI: Application Binary Interface

This is how the compiler builds an application.
It defines things (but is not limited to):
* How parameters are passed to functions (registers/stack).
* Who cleans parameters from the stack (caller/callee).
* Where the return value is placed for return.
* How exceptions propagate.

[Chromium OS docs for system calls](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)\
[x64 registers cheatsheet](./x64_cheatsheet.pdf)

