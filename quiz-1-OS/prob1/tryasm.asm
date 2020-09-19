global _start
;global checkGreater



section .text

_start:
  ;we are storing default value of rdi and rsi to check if these lines are executed or not
  mov rdi, 1110
  mov rsi, 222
  call checkGreater ;here we are calling our function
  mov rax, 60       ; exit(
  mov rdi, 0        ;   EXIT_SUCCESS
  syscall           ; );





checkGreater:

  cmp rdi, rsi
  jg pp1
  jmp pp2
addret:
  ret



pp1:
  mov rax, 1        ; write(
  mov rdi, 1        ;   STDOUT_FILENO,
  mov rsi, msg1     ;   msg1 is '1'
  mov rdx, msglen   ;   sizeof("1\n")
  syscall           ; );
  jmp addret

pp2:
  mov rax, 1        ; write(
  mov rdi, 1        ;   STDOUT_FILENO,
  mov rsi, msg0     ;   msg0 is '0', which will be printed
  mov rdx, msglen   ;   sizeof("0\n")
  syscall           ; );
  jmp addret





section .rodata
  ;msg: db "Hello, world!", 10
  msg1: db "1", 10
  msglen: equ $ - msg1
  msg0: db "0", 10
