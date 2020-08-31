default:
	@read -p "Press any key to start preprocessing step and make file hello.i ..." h;
	gcc -E hello.c -o hello.i
	@read -p "Press any key to start compilation step and make file hello.s ..." h;
	gcc -S hello.c -o hello.s
	@read -p "Press any key to start Assembling and make file hello.o ..." h;
	gcc -c hello.c -o hello.o
	@read -p "Press any key to start linking step and make the final executable file hello.out ..." h;
	gcc hello.c -o hello.out
	@read -p "All the steps are completed press any key to continue" h;

run:
	./hello.out


say_hello:
	echo "Hi, Checking if the Makefile is working"

