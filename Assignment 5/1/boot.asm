bits 16
org 0x7c00

boot:
    mov ax, 0x2401
    int 0x15 ;          enable A20 bit

mov ax, 0x3
int 0x10 ;              set vga text mode 3

lgdt [gdt_pointer] ;    load the gdt table
mov eax, cr0 
or eax,0x1 ;            set the protected mode bit on special CPU reg cr0
mov cr0, eax
jmp CODE_SEG:boot2 ;    long jump to the code segment

; Build a Global Descriptor Table with Data and Code Segments. 
gdt_start:
    dq 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:

gdt_pointer:
    dw gdt_end - gdt_start
    dd gdt_start
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32
boot2:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esi,hello
    mov ebx,0xb8000
.loop:
    lodsb
    or al,al
    jz .codepart2
    or eax,0x0100
    mov word [ebx], ax
    add ebx,2
    jmp .loop

.codepart2:
    mov edx, cr0
    mov ecx, 32          ; 32 bits in a dword
    mov ebx, 000B8170h

.loop2:
    mov eax, 130h        ; BlueOnBlack "0"
    shl edx, 1           ; Top bit to the carry flag
    adc eax, 0           ; -> AL="0" or AL="1"
    mov [ebx], ax
    add ebx, 2
    dec ecx
    jnz .loop2

halt:
    cli
    hlt
hello: db "Hello world!             value of CR0 register:",0

times 510 - ($-$$) db 0 ; The remaining bytes in the bootloader are set to 0. $ evaluates to the assembly position at the beginning of the line containing the expression; so you can code an infinite loop using JMP $. $$ evaluates to the beginning of the current section; so you can tell how far into the section you are by using ($−$$).

dw 0xaa55 ; BIOS expects the last double word (32Bytes) to be this value otherwise it will not boot.