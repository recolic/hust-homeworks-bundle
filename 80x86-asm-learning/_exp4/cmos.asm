    
    .model small
    .data
info    db 'Port No. ? $'
buffer  db 2, 1
number  db ?, ?
dos_newline   db 10, '$'
    .code
    assume ds:_data
    include rlib.inc
start:
    mov ax, _data
    mov ds, ax
    print_str_at info
    read_str_to buffer
    mov al, number 
    sub al, '0'
    out 70h, al
    in al, 71h
    xor ah, ah
    print_str_at dos_newline
    call rlib_print2d_hex
    call rlib_exit
end start
