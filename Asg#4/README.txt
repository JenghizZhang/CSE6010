compiler: gcc 9.3.0
operating system: MacOS

compile command: gcc -o integral -fopenmp integral.c -lm

run commmand: time ./integral

note:
you can modify line 9-11 to change the thread number, m, and chunk size
Because I use MacOS and it use clang, I need to change gcc to gcc-11 (11 is the verstion) to run the code

For the makefile
make ---> complie integral.c files and output the object file named integral
make run ---> run the code
make clean ---> remove the object file