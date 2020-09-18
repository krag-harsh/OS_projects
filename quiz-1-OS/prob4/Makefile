default:
	nasm -felf64 extended_add.asm -o test1.o
	nasm -felf64 long_add.asm -o test2.o
	gcc add.c test1.o test2.o -o add.out
	./add.out
run:
	./add.out


say_hello:
	echo "Hi, Checking if the Makefile is working"

