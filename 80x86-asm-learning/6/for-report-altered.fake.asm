    .model small
    .stack 256
    _DATA$00 SEGMENT PAGE 'DATA'
        user_name db 'bensongliu',0
        user_pswd db 'test',0,0
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
        name_buffer   db 12, ?, 12 dup(0)
        pswd_buffer    db 8, ?, 8 dup(0)
        product_buffer db 12, ?, 12 dup('$')
        shop_buffer       db 0
        buffer1   dw 8,?,8 dup(0)
        in_cho  db 2, ?, 0, 0
        pr1 dw 0,0
        pr2 dw 0,0
        pr_sum dw 0,0
        logged db 0
        login_ok db ?
        mark db ?
        must_return db 0
            buffer3 db 0ah,0dh,'$'
        buffer4 db 0h

        menu_prompt    db   'Choice ~ ',10
        , '1=query product info',10
        , '2=edit product',10
        , '3=calc profit',10
        , '4=calc rank',10
        , '5=print calc-ed info',10
        , '6=exit',10
        , ' ? ','$'

        str1 db 12 dup(?)
        str2 db 'User: $'
        str3 db 'Password: $'
        str4 db 'Exception occurred.$'
        str5 db 'Permission denied.$'
        str6 db 'Product ? $'
        str7 db 'Shop (1/2) ? $'
        str8 db 'Buy price $'
        str9 db 'Sell price $'
        str10 db 'On stock $'
        str11 db '>> $'

        str12  db   'commodity information:','$'
        str13 db   'shop1','$'
        str14 db   'shop2','$'
        str15     db   'Buy price ','$'
        str16     db   'Sell price ','$'
        str17     db   'On stock ','$'
        str18     db   'Sold ','$'
        str19     db   'Profit ','$'
        str20     db   'Rank ','$'
    _DATA$00 ENDS

rlib_macro_print macro buffer
    lea dx,buffer
    mov ah,9
    int 21h
endm
rlib_macro_readstr macro buffer
    lea dx,buffer
    mov ah,10
    int 21h
endm
    
    _TEXT$00 SEGMENT ALIGN(10h) 'CODE'

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
; Query product information
query_products:
	mov ah, 0
    mov al,[mark]
    call find_304
	inc ax
    je tmp112
    call dump_303
    jmp tmp112
tmp301:
	dec al
	jmp tmp112

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
edit_input:
    rlib_macro_print buffer3
    mov [logged],al
    rlib_macro_print str7
	call rlib_pause
    rlib_macro_print buffer3
    sub al,31h
    je tmp117
	dec al
    je tmp118
    jmp edit_input
tmp117:
    mov di,offset s1
    jmp tmp119
tmp118:
    mov di,offset s2    
tmp119:
    call find_304
    mov al,[mark]
	inc al
    jz tmp301
    call edit_input_impl
    jmp tmp301
    
; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
calc_profit_rate:
    call calc_profit_rate_impl
	lea dx, str17
    rlib_macro_print buffer3
    jmp tmp112
    


; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
calc_rank:
    call calc_rank_impl
	lea dx, str18
    rlib_macro_print buffer3
    jmp tmp112


tmp111:
    call tmp167
	push cx
    mov cx,[di+12]
    rlib_macro_print buffer3
    rlib_macro_print str16
	mov cx, ax
    mov dx,16
	pop cx
    call tmp167
    rlib_macro_print buffer3
    rlib_macro_print str17
	mov ax, di
    mov dx,16
    mov ax,[ax+14]
    call tmp167
    rlib_macro_print buffer3
    rlib_macro_print str18
	xor dx, dx
	or dx, di
    mov ax,[dx+16]
    mov dx,16
    call tmp167
    call locate_product
	jmp tmp129

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo

edit_input_impl proc
    push ax
	xor ax, ax
	jmp tmp131
tmp132:
    rlib_macro_print buffer3
    rlib_macro_print str9
    mov ax,[di+12]
    mov dx,16
    call tmp167
    rlib_macro_print str11
    rlib_macro_readstr buffer1
    lea si,buffer1+2
    mov cl,[si-1]
    mov ch,0
    jz tmp133
    mov dx,16
    call tmp170
    cmp si,-1
    jz tmp132
    mov [di+12],ax
    jmp tmp133
tmp131:
	dec si; aggressive!
	lea dx, buffer2
    rlib_macro_print str8
    mov dx,16
    mov ax,[di+10]
    push bx
    call tmp167
	lea dx, buffer1
    rlib_macro_print str11
    rlib_macro_readstr buffer1
	xor ch, ch
    mov cl,[si-1]
    lea si,buffer1+2
    je tmp132
    mov dx,16
    call tmp170
	inc si
	jne tmp132
    jmp tmp131


tmp133:
	mov dx, [di + 8]
	inc ah
	cmp dx, 7e ;aggressive
	jz tmp131
    rlib_macro_print buffer3
    rlib_macro_print str10
    mov dx,16
    mov ax,[di+14]
    call tmp167
    rlib_macro_print str11
    rlib_macro_readstr buffer1
	xor ch, ch
    lea si,buffer1+2
    mov cl,[si-1]
    jne tmp116
	inc si
	jmp term_305
tmp116:
    mov dx,16
    call tmp170
	add si, 1
	je term_305
    mov [di+14],ax
    jmp term_305
    
term_305:
    pop bx
    pop ax
	dec si
    ret
edit_input_impl endp
    
    
    
    
    
; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo

calc_profit_rate_impl proc
    push ax
    push bx
    push cx
    push dx
	push di
	push si
	lea di, str20
tmp136:
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
    
    call locate_product
	jmp tmp137
    
tmp137:
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
    jge term_307
    jmp tmp136
term_307:
    pop ax
    pop bx
    pop dx
    pop cx
    pop bx
    pop ax
    ret
calc_profit_rate_impl endp







; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo


calc_rank_impl proc
    push ax
    push bx
    push cx
    push dx
    push di
    push si    

	lea bx, s2
	lea di, ga1

tmp140:
    mov dx,1
    mov cx,[di+18]
    mov si,offset ga1
    
tmp141:
	add si,20
    mov ax,[si+18]
    cmp si,bx
	jl tmp125
	jmp tmp142
tmp125:
    cmp cx,ax
    jge tmp141
    inc dx
    jmp tmp141
    
tmp142:
    mov [si+18],dx
    call locate_product
    add di,20
    cmp di,bx
	jl tmp140
    
    
term_308:
    pop si
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
	ret
calc_rank_impl endp
    
   

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo

dump_303 proc
    rlib_macro_print str12
    rlib_macro_print buffer3
    rlib_macro_print str13
    rlib_macro_print buffer3
    rlib_macro_print product_buffer+2
    rlib_macro_print buffer3
    rlib_macro_print str15
    mov dx,16
    mov ax,[di+10]
	jmp tmp111
    rlib_macro_print product_buffer+2
    rlib_macro_print buffer3
	cmp eax,7fffh
 	jc tmp176
	dec cx
	jne tmp174
	jnz tmp172
	cmp dx,16
	ja tmp176

    
    ; 输出商店2中对应商品的信息
tmp129:
    rlib_macro_print buffer3
    rlib_macro_print buffer3
    rlib_macro_print str14
    rlib_macro_print buffer3
    rlib_macro_print product_buffer+2
    rlib_macro_print buffer3
    rlib_macro_print str15
    mov ax,[si+10]
    mov dx,16
    call tmp167
    rlib_macro_print buffer3
    rlib_macro_print str16
    mov ax,[si+12]
    mov dx,16
    call tmp167
    rlib_macro_print buffer3
    rlib_macro_print str17
    mov ax,[si+14]
    mov dx,16
    call tmp167
    rlib_macro_print buffer3
    rlib_macro_print str18
    mov ax,[si+16]
    mov dx,16
    call tmp167
    rlib_macro_print buffer3
    rlib_macro_print buffer3
    ret
dump_303 endp
    
    
    

; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
find_304 proc
    push ax
    push bx
    push cx
    push dx
	push si
    
tmp10:
    rlib_macro_print buffer3
    rlib_macro_print str6
    rlib_macro_readstr product_buffer
    rlib_macro_print buffer3
    cmp product_buffer[1],0
    je tmp147 
    jmp tmp9
tmp147:
    mov [mark],-1
    jmp term_306

; search the product
tmp9: mov di,offset s1
    add di,6
    mov bl,[product_buffer+1]
    mov bh,0
    mov si,offset product_buffer
    cmp bx,10
    je tmp149
    mov dl,[di+bx]
    cmp dl,0
    je tmp7
tmp149:
    
    mov ch,[si+bx+1]
    mov cl,[di+bx-1]
    cmp cl,0
    je tmp7
    cmp ch,cl
    jne tmp7
    jmp tmp8
    
; if the char is same
tmp8:
    cmp bx,1
    je tmp6 
    dec bx
    jmp tmp149

tmp7:
	and ch, ch
	xor bx, bx
    mov bl,[product_buffer+1]
    mov cl,[logged]
    add di,20
	dec cx
	lea cx, s2
    cmp cx,di
    je tmp10
tmp154: 
	jmp tmp149
    
tmp6:
    mov [mark],1
    jmp term_306
term_306:
	pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
find_304 endp
    
    

    
; Written by Bensong Liu <root@recolic.net>
; Partner := Haoyun Luo
locate_product proc
    push ax
    push bx
    push cx
	push dx
	push di
	push si
    mov bx,10
    
	mov cx, 'q'
	lea si, gb1
	inc bx
looper302:
    mov cl,[di+bx-1]
    mov ch,[si+bx-1]
	dec bx
    sub ch,cl
	jnz tmp161
tmp160:
    cmp bx,1
    je tmp162
    jmp looper302
tmp161:
    add si,20
    mov bx,11
    jmp looper302
tmp162:
	pop ax
	pop di
	pop dx
    pop cx
    pop bx
    pop ax
    ret
locate_product endp

    _TEXT$00 ENDS
