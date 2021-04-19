    ;.386
    .model small
    ;.stack 1024
    .data
    .code
    assume ds:nothing 
get_callback_from_ivt_1:
    ; arg: interrupt number in al
    ; return addr in bx
    xor ah, ah
    add ax, ax
    add ax, ax
    mov bx, ax
    xor ax, ax
    mov ds, ax
    mov es, ds:[bx+2]
    mov bx, ds:[bx]
    ret
get_callback_from_ivt_2:
    ; arg: interrupt number in al
    ; return addr in es:bx
    mov ah, 35h
    int 21h
    ret
start:
    mov al, 1h
    call get_callback_from_ivt_1
    nop
    nop
    mov al, 1h
    call get_callback_from_ivt_2
    nop
    nop
    mov al, 10h
    call get_callback_from_ivt_1
    nop
    nop
    mov al, 10h
    call get_callback_from_ivt_2
    nop
    nop
    mov ah, 4ch
    xor al, al
    int 21h
end start
