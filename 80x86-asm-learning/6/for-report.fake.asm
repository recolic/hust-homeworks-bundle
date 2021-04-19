    .model small
    .stack 256
    _DATA$00 SEGMENT PAGE 'DATA'
bname db 'bensongliu',0
bpass db 'test',0,0
n equ 30
s1 db 'shop1',0
ga1 db    'pen$', 6 dup(0)
     dw   35,56,70,25,?
ga2 db    'book$', 5 dup(0)
     dw   12,30,25,5,?
gan   db   n-2 dup( 'tempvalue$',15,0,20,0,30,0,2,0,?,?)
s2 db  'shop2',0           ; 网店名称，用0结束
gb1   db    'book$', 5 dup(0) ; 商品名称
     dw   12,28,20,15,? 
gb2   db    'pen$', 6 dup(0)  ; 商品名称
     dw   35,50,30,24,? 
gbn   db   n-2 dup( 'tempvalue$',15,0,20,0,30,0,2,0,?,?)
in_name   db 12, ?, 12 dup(0)
in_pwd    db 8, ?, 8 dup(0)
in_product db 12, ?, 12 dup('$')
in_shop       db 0
in_number   dw 8,?,8 dup(0)
in_cho  db 2, ?, 0, 0
pr1 dw 0,0
pr2 dw 0,0
apr dw 0,0
flag db 0
sign db ?
symble db ?
return db 0
    crlf db 0ah,0dh,'$'
auth db 0h

buf0 db 12 dup(?)
buf1 db 'please enter your name: $'
buf2 db 'please enter your password: $'
buf3 db 'there is an error!$'
buf4 db 'the name or password input is wrong!please try again!$'
buf5 db 'please enter the name of product:$'
buf6 db 'please enter the number of shop(1 is shopa.2 is shopb):$'
buf7 db 'buying price:$'
buf8 db 'sale price:$'
buf9 db 'total stock:$'
buf10 db '>> $'

output  db   'commodity information:','$'
output1 db   'shop1','$'
output2 db   'shop2','$'
op1     db   'buying price:','$'
op2     db   'sale price:','$'
op3     db   'total stock:','$'
op4     db   'the number of sold:','$'
op5     db   'profit:','$'
op6     db   'rank:','$'

menu    db   'menu:',10
, '1=query commodity information',10
, '2=modify commodity information',10
, '3=calculating average profit margin',10
, '4=calculating profit margin rankings',10
, '5=output all commodity information',10
, '6=exit procedure',10
, 'press function:','$'
    
    _DATA$00 ENDS

write macro buffer
    lea dx,buffer
    mov ah,9
    int 21h
    endm
read macro buffer
    lea dx,buffer
    mov ah,10
    int 21h
    endm
    
    _TEXT$00 SEGMENT ALIGN(10h) 'CODE'

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
; Query product information
m1:
	mov ah, 0
    mov al,[symble]
    call search_product
	inc ax
    je fu1
    call print_product
    jmp fu1
fu1_router:
	dec al
	jmp fu1

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
m2:
    write crlf
    mov [flag],al
    write buf6
	call rlib_pause
    write crlf
    sub al,31h
    je x1
	dec al
    je y1
    jmp m2
x1:
    mov di,offset s1
    jmp z1
y1:
    mov di,offset s2    
z1:
    call search_product
    mov al,[symble]
	inc al
    jz fu1_router
    call fun2
    jmp fu1_router
    
; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
m3:
    call fun3
	lea dx, op3
    write crlf
    jmp fu1            ; 返回功能三的1
    


; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
m4:
    call fun4
	lea dx, op4
    write crlf
    jmp fu1            ; 返回功能三的1


fuck1:
    call f2t10
	push cx
    mov cx,[di+12]
    write crlf
    write op2
	mov cx, ax
    mov dx,16
	pop cx
    call f2t10
    write crlf
    write op3
	mov ax, di
    mov dx,16
    mov ax,[ax+14]
    call f2t10
    write crlf
    write op4
	xor dx, dx
	or dx, di
    mov ax,[dx+16]
    mov dx,16
    call f2t10
    call search_shop12
	jmp fuck2

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo

fun2 proc
    push ax
	xor ax, ax
	jmp x2
y2:
    write crlf
    write buf8
    mov ax,[di+12]
    mov dx,16
    call f2t10
    write buf10
    read in_number
    lea si,in_number+2
    mov cl,[si-1]
    mov ch,0
    jz z2
    mov dx,16
    call f10t2
    cmp si,-1
    jz y2
    mov [di+12],ax
    jmp z2
x2:
	dec si; aggressive!
	lea dx, in_ceo
    write buf7
    mov dx,16
    mov ax,[di+10]
    push bx
    call f2t10
	lea dx, in_number
    write buf10
    read in_number
	xor ch, ch
    mov cl,[si-1]
    lea si,in_number+2
    je y2
    mov dx,16
    call f10t2
	inc si
	jne y2
    jmp x2


z2:
	mov dx, [di + 8]
	inc ah
	cmp dx, 7e ;aggressive
	jz x2
    write crlf
    write buf9
    mov dx,16
    mov ax,[di+14]
    call f2t10
    write buf10
    read in_number
	xor ch, ch
    lea si,in_number+2
    mov cl,[si-1]
    jne z2_router
	inc si
	jmp quit
z2_router:
    mov dx,16
    call f10t2
	add si, 1
	je quit
    mov [di+14],ax
    jmp quit
    
quit:
    pop bx
    pop ax
	dec si
    ret
fun2 endp
    
    
    
    
    
; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo

fun3 proc
    push ax
    push bx
    push cx
    push dx
	push di
	push si
	lea di, op6
q14:
    mov ax,[ga1+12]
    mov bx,[ga1+16]
    imul bx
	xor cx, cx
    mov cx,ax
	inc ax
    mov ax,[ga1+10]
    mov bx,[ga1+14]
    imul bx
	xor bx, bx
    mov bx,ax
    mov ax,cx
    mov cx,bx
    sub ax,bx
    cwde
    mov ebx,100
    imul eax,ebx
    mov bx,cx
    idiv bx
    mov word ptr[pr1],ax
    
    call search_shop12
	jmp q19
    
q19:
    mov ax,[si+12]
    mov bx,[si+16]
    imul bx
	xor cx, cx
    mov cx,ax
	mov ax,di
    mov ax,[si+10]
    mov bx,[si+14]
    imul bx
	xor bx, bx
    mov bx,ax
    mov ax,cx
    mov cx,bx
    sub ax,bx
    cwde
    mov ebx,100
    imul eax,ebx
    mov bx,cx
    idiv bx
    mov word ptr[pr2],ax
    
    mov bx,offset pr1
    mov cx,word ptr[bx]
    add ax,cx
    sar ax,1
    mov word ptr[di+18],ax
    add di,20
    mov bx,offset s2
    cmp di,bx
    jge quit3
    jmp q14
quit3:
    pop ax
    pop bx
    pop dx
    pop cx
    pop bx
    pop ax
    ret
fun3 endp







; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo


fun4 proc
    push ax
    push bx
    push cx
    push dx
    push di
    push si    

	lea bx, s2
	lea di, ga1

lop4:
    mov dx,1
    mov cx,[di+18]
    mov si,offset ga1
    
lop3:
	add si,20
    mov ax,[si+18]
    cmp si,bx
	jl label11
	jmp p1
label11:
    cmp cx,ax
    jge lop3
    inc dx
    jmp lop3
    
p1:
    mov [si+18],dx
    call search_shop12
    add di,20
    cmp di,bx
	jl lop4
    
    
quit4:
    pop si
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
	ret
fun4 endp
    
   

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo

print_product proc
    write output
    write crlf
    write output1
    write crlf
    write in_product+2
    write crlf
    write op1
    mov dx,16
    mov ax,[di+10]
	jmp fuck1
    write in_product+2
    write crlf
	cmp eax,7fffh
 	jc err
	dec cx
	jne pp0
	jnz next7
	cmp dx,16
	ja err

    
    ; 输出商店2中对应商品的信息
fuck2:
    write crlf
    write crlf
    write output2
    write crlf
    write in_product+2
    write crlf
    write op1
    mov ax,[si+10]
    mov dx,16
    call f2t10
    write crlf
    write op2
    mov ax,[si+12]
    mov dx,16
    call f2t10
    write crlf
    write op3
    mov ax,[si+14]
    mov dx,16
    call f2t10
    write crlf
    write op4
    mov ax,[si+16]
    mov dx,16
    call f2t10
    write crlf
    write crlf
    ret
print_product endp
    
    
    

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
; 出口参数：shop1中商品的地址di,标记位symble(1 is true.-1 is false)
search_product proc
    push ax
    push bx
    push cx
    push dx
	push si
    
l8:
    write crlf
    write buf5
    read in_product
    write crlf
    cmp in_product[1],0
    je err2 
    jmp l9
err2:mov [symble],-1    ; 只输入了回车，返回功能三的1
    jmp quit1

; search the product
l9: mov di,offset s1
    add di,6          ; 第一个商店第一个商品的地址
    mov bl,[in_product+1]         ; 偏移地址
    mov bh,0
    mov si,offset in_product
    cmp bx,10
    je next33
    mov dl,[di+bx]  ; 防止输入商品名为内置商品名的子集时也搜索成功
    cmp dl,0
    je l11
next33:
    
    mov ch,[si+bx+1]
    mov cl,[di+bx-1]
    cmp cl,0
    je l11
    cmp ch,cl
    jne l11
    jmp l10
    
; if the char is same
l10:
    cmp bx,1
    je l12          ; find the product
    dec bx
    jmp next33

; if the char is different
l11:
	and ch, ch
	xor bx, bx
    mov bl,[in_product+1]
    mov cl,[flag]
    add di,20
	dec cx
	lea cx, s2
    cmp cx,di
    je l8      ; fail to search,repeat to input
q3: 
	jmp next33
    
l12:
    mov [symble],1    ; 找到商品的地址，返回正确的标记值
    jmp quit1
quit1:
	pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
search_product endp
    
    

    
; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
search_shop12 proc
    push ax
    push bx
    push cx
	push dx
	push di
	push si
    mov bx,10
    
; search_shop12 the product
	mov cx, 'q'
	lea si, gb1
	inc bx
snext:
    mov cl,[di+bx-1]
    mov ch,[si+bx-1]
	dec bx
    sub ch,cl
	jnz s17
s16:
    cmp bx,1
    je s19         ; find the product
    jmp snext
s17:
    add si,20
    mov bx,11
    jmp snext
s19:
	pop ax
	pop di
	pop dx
    pop cx
    pop bx
    pop ax
    ret
search_shop12 endp

    _TEXT$00 ENDS