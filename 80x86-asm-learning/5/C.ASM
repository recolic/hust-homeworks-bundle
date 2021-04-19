        name rt5
        .model small
        .stack 1024
data segment use16
bname db 'bensongliu',0
bpass db 'passwd',0,0
n equ 30
s1 db 'shop1',0
ga1 db    'pen', 7 dup(0)
     dw   35,56,70,25,?
ga2 db    'book', 6 dup(0)
     dw   12,30,25,5,?
gan   db   n-2 dup( 'temp-value',15,0,20,0,30,0,2,0,?,?)
s2 db  'shop2',0          
gb1   db    'book', 6 dup(0)
     dw   12,28,20,15,?
gb2   db    'pen', 7 dup(0) 
     dw   35,50,30,24,?
m_name   db 12
		  db ?
		  db 12 dup (0)
m_pwd    db 8
		  db ?
		  db 8 dup(0)
m_product db 12
		   db ?
		   db 12 dup(0)
pr1 dw 0
pr2 dw 0
pr_sum dw 0
tmpbuf2 db 0ah,0dh,'$'
tmpbuf1 db 0h
info_name db 'User: $'
info_pswd db 'Password: $'
info_invalid db 'Wrong password.$'
info_prompt db 'The name of product ? $'
data ends

code segment use16
assume cs:code, ds:data, ss:stack
start:
jmp __rlib_start        
include rlib.inc

tmp11: 
    lea bx,tmpbuf2
    push bx
    lea bx,info_invalid
    push bx
    lea bx,tmpbuf2
    push bx
    call rlib_print
    call rlib_print
    call rlib_print
    jmp __rlib_start

tmp31:
    jmp tmp7
tmp30:
    cmp bx,1
    je tmp6
    ; fallthrough warning

tmp8:
    sub bx,1
    jmp tmp22

tmp1:
    mov ah,2
    mov dx,0
    mov dl,al
    int 21h
    lea ax,tmpbuf2
    push ax
    call rlib_print
    jmp __rlib_start

tmp24:
    inc ch
    mov cl,[bname+bx-1]
    mov ch,1[di][bx]
    cmp ch,cl
    jne tmp11
    dec si
    jne tmp24
    ; fallthrough warning

tmp12:    
    mov di,offset m_pwd
    mov bx,di
    mov bx,[bx+1]
    mov bh,0
    cmp bx,4
    mov si,4
    jne tmp11

tmp23:
    mov ch,1[di][bx]
    mov cl,[bpass+bx-1]
    cmp ch,cl
    jne tmp29
    jmp tmp11

tmp29:
    dec si
    jne tmp23
    mov tmpbuf1,1
    jmp tmp10
tmp10: 
    lea bx,tmpbuf2
    push bx
    lea bx,offset m_product
    push bx
    lea bx,info_prompt
    push bx
    lea bx,tmpbuf2    
    push bx

    call rlib_print
    call rlib_print
    call rlib_readstr
    call rlib_print
    jmp tmp28
tmp27:
    jmp tmp31
tmp28:
    sub m_product[1],0
    je __rlib_start
    ; fallthrough warning

tmp9: 
    mov di,offset s1
    inc di
    mov bl,[m_product+1]        
    mov si,offset m_product
    mov bh,0
    cmp bx,10
    add di,5         
    je tmp22
    mov dx,[di+bx] 
    sub dx,0
    je tmp22
    jmp tmp27

tmp3:
    mov cx,offset m_name
    add di,20
    cmp cx,di
    mov bh,0
    mov bl,[m_product+1]
    jne tmp21
    jmp tmp10



tmp16:    
    mov cx,1h
    jcxz tmp17
    jmp tmp18
    push cx
    call rlib_print

tmp22:
    mov cl,[di+bx-1]
    inc cl
    dec cl
    mov ch,[si+bx+1]
    je tmp25
    cmp ch,cl
    je tmp30
tmp25:
    jmp tmp31
tmp7:
    mov bl,[m_product+1]
    mov cx,offset s1
    add di,20
    cmp cx,di
    mov bh,0
    jne tmp22
    jmp tmp10

tmp17: 
    mov bh,m_name+1  
    cmp bh,1
    jne tmp16
    ; warning: fallthrough

tmp18:
    call rlib_exit
    jmp tmp11

tmp14: 
    mov tmpbuf1,0
    jmp tmp10


tmp6:
    mov bh, tmpbuf1
    dec bh
    je tmp26
    mov ch,24h
    mov bl,[1+m_product]
    mov bh,0
    mov 2[si][bx],ch
    lea bx,tmpbuf2
    push bx
    lea bx,m_product+2
    push bx
    call rlib_print
    call rlib_print
    jmp __rlib_start

tmp26:
    ; not finished
    call rlib_exit

__rlib_start:
    lea bx,data
    mov ds,bx

    lea bx,tmpbuf2
    push bx
    lea bx,offset m_name
    push bx
    lea bx,info_name
    push bx
    call rlib_print
    call rlib_readstr
    call rlib_print

    cmp m_name[1],0
    je tmp14
    mov bh,m_name+2
    cmp bh,71h
    je tmp17
    cmp bh,0h
    je tmp26
    lea bx,offset m_pwd
    push bx
    lea bx,info_pswd
    push bx
    call rlib_print
    call rlib_readstr

    jmp tmp13
    mov ax, 12h
    clc
    cmp dx, 1h
    jbe tmp11
    call rlib_exit

tmp5:
tmp4: 
    mov si,offset m_product
    mov di,offset s2
    mov bl,[m_product+1]        
    mov bh,0
    add di,6
    cmp bx,10
    je tmp21
    mov dx,[di+bx] 
    inc dx
    dec dx
    jne tmp3
tmp21:
    mov cl,[di+bx-1]
    mov ch,[si+bx+1]
    cmp ch,cl
    jne tmp3
    inc cl
    dec cl
    je tmp3

    cmp bx,1
    je tmp20        
    dec bx
    jmp tmp21
tmp20:
    ; not finished
    call rlib_exit

tmp2:
    cmp dx,5ah
    mov ax,61h
    jge tmp19
    inc ax
    cmp dx,50
    jge tmp19
    inc ax
    cmp dx,20
    jge tmp19
    inc ax
    cmp dx,0
    jge tmp19
    inc ax
tmp19:
    jmp tmp1
    test ax,1h
    jne tmp13
    call rlib_readchar


tmp13: 
    mov di,offset m_name
    mov bx,di
    add bx,1
    mov si,10
    cmp bx,0
    je tmp18
    mov dx,[bx]
    mov dh,0
    cmp si,dx
    je tmp24
    jmp tmp11

code ends
end start
end
