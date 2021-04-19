    name rt4
    .model small
    .stack 1024
    .data
buf db 'xuehao',?,?,?,?,0ah,'$'
num db '4531'
    .code
    jmp __rlib_start
    include rlib.inc
__rlib_start:
    mov ax, @data
    mov ds, ax
    ;寄存器间接寻址
    mov si, offset num
    mov bx, offset buf + 6
    mov di, [si]
    mov [bx], di
    ;变址寻址
    mov al, num + 1 
    mov 1[bx], al
    ;基址加变址寻址
    mov si, 1
    mov al, num + 2 
    mov 1[bx][si], al
 
    ;直接寻址
    mov al, num + 3 
    mov byte ptr buf + 9, al
    lea bx, buf 
    
    push bx
    call rlib_print
    call rlib_exit
end __rlib_start
end
