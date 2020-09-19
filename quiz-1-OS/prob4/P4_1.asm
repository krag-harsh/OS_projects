section .text
    global long_add
 
long_add:

    push ebp
    mov  ebp, esp
    
    mov  eax, [ebp+8]
    add  eax, [ebp+12]
    add  eax, [ebp+16]
    add  eax, [ebp+20]
    mov  esp, ebp
    pop  ebp
    ret                        ; we return the value stored in register eax

   	; mov     eax, edi          ; register edi initially holds a, it is then copied to eax
    ; add     eax, esi          ; register esi initially holds b , it is then added to the value in eax and stored back to eax
    ; add     eax, edx
    ; add     eax, ecx
    
    
;nasm -felf32 long_add.asm && gcc -m32 add.c long_add.o && ./a.out
;sudo apt-get install gcc-9-multilib