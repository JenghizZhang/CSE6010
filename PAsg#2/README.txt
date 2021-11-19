operating system: Linux

compile command: gcc *.c -g -o output

run commmand: 
./output src dest (defalut)	
./output src dest -swap (swap transformation enabled)
src and dest should be numbers.
example: ./output 14 25 -swap

note:
if you want to print out my adjacency list, you can uncomment line 28 - line 39 from wordchains.c and recompile it.

For the makefile
make ---> complie all .c files and output the object file named output
make run ARGS="src dest" ---> run the code without swap transformation, src and dest are the indexs of words
       example: make run ARGS="10 19"
make swap ARGS="src dest" ---> run the code with swap transformation, src and dest are the indexs of words
       example: make swap ARGS="10 19"
make clean ---> remove the object file