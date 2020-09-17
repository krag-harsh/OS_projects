section .text
    global add
 
add:



   	mov     rax, rdi          ; register rdi initially holds a, it is then copied to rax
    add     rax, rsi          ; register rsi initially holds b , it is then added to the value in rax and stored back to rax
    add     rax, rdx
    add     rax, rcx
    
    ret                       ; we return the value stored in register rax

