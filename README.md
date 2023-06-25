# safeAlloc
This library enhances the development process of projects by making the `malloc` function safer. The `safeAlloc()` function allocates memory and keeps track of the allocated memory blocks in a struct list, while also recording information such as the line number and size in the `safeAlloc` file. The `safeFree()` function removes the freed memory blocks from both the struct and the `safeAlloc` file, making it easier to identify unfreed memory. When exiting the program using the `safeExit()` function, all memory addresses in the struct are traversed and freed, allowing you to test your program safely.<br>
How To Use<br>
When you compile using the make command, you will see the output safeAlloc.a. After adding safeAlloc.h to your C library, compile your program with safeAlloc.a.<br>
Linkedin: https://www.linkedin.com/in/hiqermod/
