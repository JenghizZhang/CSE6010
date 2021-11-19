compiler: gcc 9.3.0
operating system: Ubuntu 20.04.3 LTS (via WSL2)

note: you can modify the 7th line in header.h to change the file

compile command: gcc voting.c methodPair1.c methodPair2.c -o voting

run commmand: 
./voting (defalut)	
./voting d (with detail description)	

For the makefile
make ---> complie .c files and output the object file named voting
make default ---> run the code (default))
make detail ---> run the code with description
make clean ---> remove the object file