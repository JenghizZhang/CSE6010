compiler: gcc 9.3.0
operating system: Ubuntu 20.04.3 LTS (via WSL2)

compile command: gcc gates.c -g -o gates

run commmand: 
./gates (defalut:inserstion sort)	
./gates i (inserstion sort)	
./gates q (quick sort)	
./gates h (heap sort)	

note:
you can uncomment 333 and 334 lines if you want to check the sorted data

For the makefile
make ---> complie gates.c files and output the object file named gates
make insertion ---> run the code based on insertion sort
make heap ---> run the code based on heap sort
make quick ---> run the code based on quick sort
make clean ---> remove the object file