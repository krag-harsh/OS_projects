section .text
    global long_add
 
long_add:



   	mov     eax, edi          ; register edi initially holds a, it is then copied to eax
    add     eax, esi          ; register esi initially holds b , it is then added to the value in eax and stored back to eax
    add     eax, edx
    add     eax, ecx
    
    ret                       ; we return the value stored in register eax

