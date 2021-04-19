print_str_at   macro addr
        push ax
        push dx
        mov ah, 9
        lea dx, addr
        int 21h
        pop dx
        pop ax
        endm

read_str_to  macro addr
        push ax
        push dx
        lea dx, addr
        mov ah, 10
        int 21h
        pop dx
        pop ax
        endm

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

rlib_showtime proc
    push ax
    push bx
    push cx
    push dx
    mov ah, 2ch
    int 21h
    mov bx, dx

    mov al, ch
    xor ah, ah
    call rlib_print2d
    mov dl, ':'
    mov ah, 02h
    int 21h

    mov al, cl
    xor ah, ah
    call rlib_print2d
    mov dl, ':'
    mov ah, 02h
    int 21h

    mov al, bh
    xor ah, ah
    call rlib_print2d
    mov dl, ':'
    mov ah, 02h
    int 21h

    mov al, bl
    xor ah, ah
    call rlib_print2d
    mov dl, 10
    mov ah, 02h
    int 21h
 
    pop dx
    pop cx
    pop bx
    pop ax
    ret
rlib_showtime endp

rlib_print2d:
    ;; input in ax (0-99)
    ;; clobbers ax and dx, save them if needed
    mov dl, 0ah ; divide by: 10
    div dl      ; first digit in al (quotient), second digit in ah (remainder)
    mov dx, ax  ; save the digits
    add al, 30h ; ascii '0'
    mov ah, 0eh ; set up print
    int 10h     ; print first digit.
    mov al, dh  ; retrieve second digit
    add al, 30h
    int 10h     ; print it
    ret

rlib_print2d_hex_as_dec:
    ;; input in ax (0-ff)
    ;; clobbers ax and dx, save them if needed
    mov dl, 10h ; divide by: 16
    div dl      ; first digit in al (quotient), second digit in ah (remainder)
    mov dx, ax  ; save the digits
    add al, 30h ; ascii '0'
    mov ah, 0eh ; set up print
    int 10h     ; print first digit.
    mov al, dh  ; retrieve second digit
    add al, 30h
    int 10h     ; print it
    ret

rlib_print2d_hex:
    ;; input in ax (0-ff)
    ;; clobbers ax and dx, save them if needed
    mov dl, 10h ; divide by: 16
    div dl      ; first digit in al (quotient), second digit in ah (remainder)
    mov dx, ax  ; save the digits
    add al, 30h ; al += '0'
    ; if al > 39h { al += 39; }
    cmp al, 39h
    jle _rlib_skip
    add al, 39
_rlib_skip:
    ; endif
    mov ah, 0eh ; set up print
    int 10h     ; print first digit.
    mov al, dh  ; retrieve second digit
    add al, 30h
    ; if al > 39h { al += 39; }
    cmp al, 39h
    jle _rlib_skip_2
    add al, 39
_rlib_skip_2:
    ; endif 
    int 10h     ; print it
    ret


