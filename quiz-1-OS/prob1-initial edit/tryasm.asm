;global _start

global checkGreater
; type checkGreater, @function 

section .text

;;rdi,rsi
_start:

  mov rdi, 1110
  mov rsi, 222
  call checkGreater
  mov rax, 60       ; exit(
  mov rdi, 0        ;   EXIT_SUCCESS
  syscall           ; );





checkGreater:
  ; .fnstart
  cmp rdi, rsi
  jl pp1
  jmp pp2
addret:
  ret
  ; .fnend


pp1:
  mov rax, 1        ; write(
  mov rdi, 1        ;   STDOUT_FILENO,
  mov rsi, msg1      ;   
  mov rdx, msglen   ;   sizeof("1\n")
  syscall           ; );
  jmp addret

pp2:
  mov rax, 1        ; write(
  mov rdi, 1        ;   STDOUT_FILENO,
  mov rsi, msg0      ;   
  mov rdx, msglen   ;   sizeof("0\n")
  syscall           ; );
  jmp addret





section .rodata
  ;msg: db "Hello, world!", 10
  msg1: db "1", 10
  msglen: equ $ - msg1
  msg0: db "0", 10