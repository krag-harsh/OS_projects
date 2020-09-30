default:
	@read -p "Press any key to start preprocessing step and make file q1.i ..." h;
	gcc -E q1.c -o q1.i
	@read -p "Press any key to start compilation step and make file q1.s ..." h;
	gcc -S q1.c -o q1.s
	@read -p "Press any key to start Assembling and make file q1.o ..." h;
	gcc -c q1.c -o q1.o
	@read -p "Press any key to start linking step and make the final executable file q1.out ..." h;
	gcc q1.c -o q1.out

run:
	./q1.out