
r_getchar_impl:
    ; Arg: -
    ; Return: result in al
    ; Destroy: ax
    mov ah, 01h
    int 21h
    ret

r_print_impl:
    ; Arg: string addr in ax
    ; Return: -
    ; Destroy: ax
    push dx
    mov dx, ax
    mov ah, 9
    int 21h
    pop dx
    ret

r_exit_impl:
    mov ah, 4ch
    xor al, al
    int 21h
    ; no return
