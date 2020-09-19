default:
	nasm -felf64 P4_2.asm -o test2.o
	gcc P4.c test2.o -o add.out
	./add.out

trytt:
	nasm -felf32 P4_1.asm -o test2.o
	gcc -m32 P4.c test2.o -o add.out
	./add.out

run:
	./add.out


say_hello:
	echo "Hi, Checking if the Makefile is working"

