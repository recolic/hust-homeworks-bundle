    
    .model small
    .data
    .code
    assume ds:_data
    include rlib.inc
start:
    mov ax, 4ah    
    call rlib_print2d_hex
    call rlib_exit
end start
