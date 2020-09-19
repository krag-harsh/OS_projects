default:
	nasm -felf64 tryasm.asm -o test.o
	ld test.o -o ou.out
	./ou.out
	
onlyc:
	nasm -felf64 tryasm.asm -o test.o
	gcc -c add.c -o li.o
	gcc li.o test.o -o add.out
	./add.out


say_hello:
	echo "Hi, Checking if the Makefile is working"

