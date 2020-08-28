section .text
    global add
 
add:
   	mov     rax, rdi          ; result (rax) initially holds x
    add     rax, rsi  
    ret

