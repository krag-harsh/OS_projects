default:
	nasm -felf64 add.asm -o test.o
	gcc add.c test.o -o add.out
	./add.out
	
asmonly:
	nasm -felf64 add.asm -o test.o
	ld test.o -o ou.out
	./ou.out

asmc:
	nasm -felf64 tryasm.asm -o test.o
	gcc add.c test.o -o add.out
	./add.out

say_hello:
	echo "Hi, Checking if the Makefile is working"

