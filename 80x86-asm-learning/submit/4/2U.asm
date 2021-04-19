.386
code segment use16
start:  xor ax, ax
        mov ds, ax
        mov ax, ds:[16h * 4]
        mov cx, ds:[16h * 4 + 2]
        mov es, cx
        sub ax, 4
        cli
        mov si, ax
        mov bx, es:[si]
        mov word ptr ds:[16h * 4], bx
        add si, 2
        mov ax, es:[si]
        mov ds:[16h * 4 + 2], ax
        sti
        int 49h
        mov ax, 4c00h
        int 21h
code ends
end start
