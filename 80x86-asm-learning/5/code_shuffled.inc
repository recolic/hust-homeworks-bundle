    jmp __rlib_start

l7: 
    lea bx,crlf
    push bx
    lea bx,buf4
    push bx
    lea bx,crlf
    push bx
    call rlib_print
    call rlib_print
    call rlib_print
    jmp __rlib_start

label4:
    jmp l11
label5:
    cmp bx,1
    je l12
    ; fallthrough warning

l10:
    sub bx,1
    jmp next3

l21:
    mov ah,2
    mov dx,0
    mov dl,al
    int 21h
    lea ax,crlf
    push ax
    call rlib_print
    jmp __rlib_start

next1:
    inc ch
    mov cl,[bname+bx-1]
    mov ch,1[di][bx]
    cmp ch,cl
    jne l7
    dec si
    jne next1
    ; fallthrough warning

l6:    
    mov di,offset in_pwd
    mov bx,di
    mov bx,[bx+1]
    mov bh,0
    cmp bx,4
    mov si,4
    jne l7

next2:
    mov ch,1[di][bx]
    mov cl,[bpass+bx-1]
    cmp ch,cl
    je label1
    jmp l7

label1:
    dec si
    jne next2
    mov auth,1
    jmp l8
l8: 
    lea bx,crlf
    push bx
    lea bx,offset in_product
    push bx
    lea bx,buf5
    push bx
    lea bx,crlf    
    push bx

    call rlib_print
    call rlib_print
    call rlib_call10
    call rlib_print
    jmp label3
label2:
    jmp label4
label3:
    sub in_product[1],0
    je __rlib_start
    ; fallthrough warning

l9: 
    mov di,offset s1
    inc di
    mov bl,[in_product+1]        
    mov si,offset in_product
    mov bh,0
    cmp bx,10
    add di,5         
    je next3
    mov dx,[di+bx] 
    sub dx,0
    je next3
    jmp label2

l17:
    mov cx,offset in_name
    add di,20
    cmp cx,di
    mov bh,0
    mov bl,[in_product+1]
    jne next4
    jmp l8



l3:    
    mov cx,1h
    jcxz l2
    jmp l1
    push cx
    call rlib_print

next3:
    mov cl,[di+bx-1]
    inc cl
    dec cl
    mov ch,[si+bx+1]
    je label8
    cmp ch,cl
    je label5
label8:
    jmp label4
l11:
    mov bl,[in_product+1]
    mov cx,offset s1
    add di,20
    cmp cx,di
    mov bh,0
    jne next3
    jmp l8

l2: 
    mov bh,in_name+1  
    cmp bh,1
    jne l3
    ; warning: fallthrough

l1:
    call rlib_exit
    jmp l7

l4: 
    mov auth,0
    jmp l8


l12:
    mov bh, auth
    dec bh
    je l13
    mov ch,24h
    mov bl,[1+in_product]
    mov bh,0
    mov 2[si][bx],ch
    lea bx,crlf
    push bx
    lea bx,in_product+2
    push bx
    call rlib_print
    call rlib_print
    jmp __rlib_start

l13:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;do not edit
    add di,10
    mov ax,[di+2]
    mov bx,[di+6]
    imul ax,bx
    mov bx,[di]
    mov cx,[di+4]
    imul bx,cx
    mov cx,bx
    sub ax,bx
    cwd
    mov bx,100
    imul ax,bx
    mov bx,cx
    idiv bx
    mov bx,offset pr1
    mov [bx],ax
    jmp l14

__rlib_start:
    mov bx,bname
    mov ds,bx

    lea bx,crlf
    push bx
    lea bx,offset in_name
    push bx
    lea bx,buf1
    push bx
    call rlib_print
    call rlib_call10
    call rlib_print

    cmp in_name[1],0
    je l4
    mov bh,in_name+2
    cmp bh,71h
    je l2
    cmp bh,0h
    je l13
    lea bx,offset in_pwd
    push bx
    lea bx,buf2
    push bx
    call rlib_print
    call rlib_call10

    jmp l5
    mov ax, 12h
    clc
    cmp dx, 1h
    jbe l7
    call rlib_exit

l14:
l15: 
    mov si,offset in_product
    mov di,offset s2
    mov bl,[in_product+1]        
    mov bh,0
    add di,6
    cmp bx,10
    je next4
    mov dx,[di+bx] 
    inc dx
    dec dx
    jne l17
next4:
    mov cl,[di+bx-1]
    mov ch,[si+bx+1]
    cmp ch,cl
    jne l17
    inc cl
    dec cl
    je l17

    cmp bx,1
    je l19        
    dec bx
    jmp next4
l19:
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;do not edit 
    add di,10
    mov ax,[di+2]
    mov bx,[di+6]
    imul ax,bx
    mov bx,[di]
    mov cx,[di+4]
    imul bx,cx
    mov cx,bx
    sub ax,bx
    cwd
    mov bx,100
    imul ax,bx
    mov bx,cx
    idiv bx

    mov bx,offset pr2
    mov [bx],ax
    mov di,offset pr1
    mov ax,[di]
    cwd
    add ax,[bx]
    mov bx,2
    idiv bx
    mov bx,offset apr
    mov [bx],ax
    jmp l20


l20:
    cmp dx,5ah
    mov ax,61h
    jge label6
    inc ax
    cmp dx,50
    jge label6
    inc ax
    cmp dx,20
    jge label6
    inc ax
    cmp dx,0
    jge label6
    inc ax
label6:
    jmp l21
    test ax,1h
    jne l5
    call rlib_readchar


l5: 
    mov di,offset in_name
    mov bx,di
    add bx,1
    mov si,10
    cmp bx,0
    je l1
    mov bx,[bx]
    xor bh,bh
    cmp si,bx
    je next1
    jmp l7


