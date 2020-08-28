default:
	@read -p "Press any key to start preprocessing step and make file hello.i ..." h;
	nasm -felf64 add.asm -o test.o
	@read -p "Press any key to start compilation step and make file hello.s ..." h;
	gcc -no-pie add.c test.o -o add.out
run:
	./add.out


say_hello:
	echo "Hi, Checking if the Makefile is working"

