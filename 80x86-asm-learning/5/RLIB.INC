rlib_print proc
    ; print string to stdout(dos, 16)
    ; Arg: word ptr to_print
    pop ax
    pop dx
    push ax

    mov ah, 9
    int 21h
    ret
rlib_print endp

rlib_readstr proc
    ; dos syscall 10(dos, 16)
    ; Arg: word ptr to_print
    pop ax
    pop dx
    push ax

    mov ah, 10
    int 21h
    ret
rlib_readstr endp

rlib_pause proc
    ; pause
    ; Arg: 
    mov ah, 1
    int 21h
    ret
rlib_pause endp

rlib_readchar proc
    ; readchar
    ; Arg: word ptr target
    pop ax
    pop bx
    push ax
    mov ah, 1
    int 21h
    mov ah, 0
    mov [bx], ax
    ret
rlib_readchar endp

rlib_readchar_noecho proc
    ; readchar(noecho)
    ; Arg: word ptr target
    pop ax
    pop bx
    push ax
    mov ah, 8
    int 21h
    mov ah, 0
    mov [bx], ax
    ret
rlib_readchar_noecho endp

rlib_exit proc
    ; libc exit
    ; Arg:
    mov ah, 4ch
    mov al, 00h
    int 21h
rlib_exit endp
