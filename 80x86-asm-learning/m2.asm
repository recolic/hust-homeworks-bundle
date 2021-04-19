.386

stack segment use16 stack
        db 200 dup(0)
stack ends

data segment use16
bname db 'bensongliu',0
bpass db 'test',0,0
n equ 30
s1 db 'shop1',0
ga1 db    'pen$', 6 dup(0)
     dw   11,22,33,44,?
ga2 db    'book$', 5 dup(0)
     dw   55,66,77,88,?
gan   db   n-2 dup( 'tempvalue$',15,0,20,0,30,0,2,0,?,?)
s2 db  'shop2',0           ;网店名称，用0结束
gb1   db    'book$', 5 dup(0) ; 商品名称
     dw   1,2,3,4,? 
gb2   db    'pen$', 6 dup(0)  ; 商品名称
     dw   31,32,33,44,? 
gbn   db   n-2 dup( 'tempvalue$',15,0,20,0,30,0,2,0,?,?)
in_name   db 12
		  db ?
		  db 12 dup (0)
in_pwd    db 8
		  db ?
		  db 8 dup(0)
in_product db 12
		   db ?
		   db 12 dup('$')
in_shop	   db 0
in_number dw 8
			dw ?
			dw 8 dup(0)
in_cho  db 2
        db ?
        db 2 dup(0)
pr1 dw 0,0
pr2 dw 0,0
apr dw 0,0
flag db 0
sign db ?
symble db ?
return db 0
crlf db 0ah,0dh,'$'
auth db 0h


        menu    db   'choice ~ ',10
        db '1, query product info',10
        db '2, edit product',10
        db '3, calc profit',10
        db '4, calc rank',10
        db '5, print calc-ed info',10
        db '6, exit',10
        db ' ? ','$'

        buf0 db 12 dup(?)
        buf1 db 'user: $'
        buf2 db 'password: $'
        buf3 db 'exception occurred.$'
        buf4 db 'permission denied.$'
        buf5 db 'product ? $'
        buf6 db 'shop (1/2) ? $'
        buf7 db 'buy price $'
        buf8 db 'sell price $'
        buf9 db 'on stock $'
        buf10 db '>> $'

        output  db   'commodity information:','$'
        output1 db   'shop1','$'
        output2 db   'shop2','$'
        op1     db   'buy price ','$'
        op2     db   'sell price ','$'
        op3     db   'on stock ','$'
        op4     db   'sold ','$'
        op5     db   'profit ','$'
        op6             db   'rank ','$'
data ends

code segment use16
        assume cs:code, ds:data, ss:stack
		write macro a
			lea dx,a
			mov ah,9
			int 21h
			endm
		read macro a
			lea dx,a
			mov ah,10
			int 21h
			endm
start:
	;input the name and password
	mov ax,data
	mov ds,ax
	lea dx,buf1
	mov ah,9
		int 21h
	lea dx,offset in_name
	mov ah,10
		int 21h
	lea dx,crlf
	mov ah,9
	int 21h
	
	;judge if it is legal
	cmp in_name[1],0
	je l4
	mov bh,in_name+2
	cmp bh,'q'
	je l2
	lea dx,buf2
	mov ah,9
		int 21h
	lea dx,offset in_pwd
	mov ah,10
		int 21h
		
	;judge if the name right
	jmp l5
	;judge if the password right
	jmp l6
	
	mov ax, 4c00h
        int 21h	
	

	
		
l1:mov ax, 4c00h      ;end
        int 21h	
	
	
l2: mov bh,in_name+1   ;judge if it is 'q'
	cmp bh,1
	je l1

l3:	mov ax, 4c00h;quit
        int 21h

l4: 
	mov auth,0
	jmp fu1
		

;judge whether the name is right	
l5: 
	mov di,offset in_name
	mov bx,di
	inc bx
	mov si,10
	mov bx,[bx]
	mov bh,0
	cmp si,bx
	jne l7

	
next1:
	mov ch,1[di][bx]
	mov cl,[bname+bx-1]
	cmp ch,cl
	jne l7
	dec si
	jne next1
	jmp l6
	
;judge whether the password is right
l6:	mov di,offset in_pwd
	mov bx,di
	inc bx
	mov si,4
	mov bx,[bx]
	mov bh,0 
	cmp si,bx
	jne l7

next2:
	mov ch,1[di][bx]
	mov cl,[bpass+bx-1]
	cmp ch,cl
	jne l7
	dec si
	jne next2
	mov auth,1h
	jmp fu1
		
l7: lea dx,crlf
	mov ah,9
	int 21h
	lea dx,buf4
	mov ah,9
	int 21h
	lea dx,crlf
	mov ah,9
	int 21h
	jmp start
		
		
		
;编写者：潘璐。
;同组同学：潘许飞。
;函数功能：菜单显示
fu1: 
	cmp auth,0
	jz lm0
	jmp lm1
lm0:
	write crlf
	write menu
	read in_cho
	write crlf
	lea di,in_cho+2
	mov al,[di]
	cmp al,'1'
	jz m1
	cmp al,'6'
	jz exit
	jmp start
lm1:write crlf
	write menu
    
	read in_cho
	lea di,in_cho+2
	mov al,[di]
	cmp al,'1'
	jz m1
	cmp al,'2'
	jz m2
	cmp al,'3'
	jz m3
	cmp al,'4'
	jz m4
	cmp al,'5'
	jz m5
	cmp al,'6'
	jz exit
	write buf3
    write crlf
	jmp lm1
	
	
	
	
;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：查询商品信息
m1:call search_product
	mov al,[symble]
	cmp al,-1
	jz fu1
	call print_product
	jmp fu1
	
;编写者：潘许飞。
;同组同学：潘璐。
;修改商品信息的功能，主要是进行用户输入的准备工作。
;实际的数据修改操作在函数fun2中进行。
m2:
	write crlf
	write buf6
	mov ah,1
	int 21h
	write crlf
	mov [flag],al
	cmp al,'1'
	jz x1
	cmp al,'2'
	jz y1
	jmp m2;输入非法，重新输入。
x1:	mov di,offset s1
	jmp z1
y1:	mov di,offset s2	
	jmp z1
z1:call search_product
	mov al,[symble]
	cmp al,-1
	jz fu1
	call fun2
	jmp fu1
	
;编写者：潘许飞。
;同组同学：潘璐。
;功能：调用函数，计算利润率。(具体函数模块在之后统一给出。)
m3:call fun3
	write crlf
	jmp fu1			;返回功能三的1
	


;编写者：潘许飞。
;同组同学：潘璐。
;功能：调用函数，统计利润率的排名。(具体函数模块在之后统一给出。)
m4:call fun4
   write crlf
   jmp fu1			;返回功能三的1
	
	

;编写者：潘璐。
;同组同学：潘许飞。
;函数功能：输出全部商品信息
m5:write output
    write crlf
	write output1
	write crlf
	mov cx,3
	lea di,s1+6
	jmp n_1

n_1:write crlf
	write [di]
	write crlf
	write op1
	mov ax,[di+10]
	mov dx,16
	call f2t10
	write crlf
	write op2
	mov ax,[di+12]
	mov dx,16
	call f2t10
	write crlf
	write op3
	mov ax,[di+14]
	mov dx,16
	call f2t10
	write crlf
	write op4
	mov ax,[di+16]
	mov dx,16
	call f2t10
    write crlf
	cmp flag,0
	jz co1
	jmp co2
co1:write op5
	jmp con
co2:write op6
	jmp con
con:mov ax,[di+18]
	mov dx,16
	call f2t10
	write crlf
n_2:add di,20
	dec cx
	jnz n_1
	cmp flag,1
	jz fu1
	
n_3:mov flag,1
    write output2
	write crlf
	mov cx,3
	lea di,gb1
	jmp n_1
		


	
exit: mov ah,4ch
      int 21h

	

	
	

;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：修改商品信息
;入口参数：无。
;出口参数：是否找到、是否是回车、或者修改成功的信息

fun2 proc
	push ax
	push bx
x2:	write buf7
	mov ax,[di+10]
	mov dx,16
	call f2t10
	write buf10
	read in_number
	lea si,in_number+2
	mov cl,[si-1]
	mov ch,0
	jz y2
	mov dx,16
	call f10t2
	cmp si,-1
	jz x2
	mov [di+10],ax
	jmp y2

	
y2:	write crlf
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
z2:
	write crlf
	write buf9
	mov ax,[di+14]
	mov dx,16
	call f2t10
	write buf10
	read in_number
	lea si,in_number+2
	mov cl,[si-1]
	mov ch,0
	jz quit
	mov dx,16
	call f10t2
	cmp si,-1
	jz z2
	mov [di+14],ax
	jmp quit
	
quit:
	pop bx
	pop ax
	ret;返回后需要返回至功能三的1
fun2 endp
	
	
	
	
	
;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：计算平均利润率
;入口参数：无。
;出口参数：无。

fun3 proc
	push ax
	push bx
	push cx
	push dx

	

	mov di,offset ga1
q14:
	mov bx,[di+16]
	mov ax,[di+12]
	imul bx
	mov cx,ax
	mov bx,[di+14]
	mov ax,[di+10]
	imul bx
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
	
q19:
	mov bx,[si+16]
	mov ax,[si+12]
	imul bx
	mov cx,ax
	mov bx,[si+14]
	mov ax,[si+10]
	imul bx
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
quit3:pop dx
	pop cx
	pop bx
	pop ax
	
	ret
fun3 endp







;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：计算利润率排名
;入口参数：无。
;出口参数：无。

fun4 proc
	push ax
	push bx
	push cx
	push dx
	
	mov di,offset ga1
	mov dx,offset s2

lop4:			;外层循环，每个商品依次计算
	mov cx,1	;计数，用作排名
	mov ax,[di+18]
	mov si,offset ga1
	
lop3:add si,20      ;内层循环，计算单个商品利润率排名
	cmp si,dx
	jge p1
	mov bx,[si+18]
	cmp ax,bx
	jge lop3
	inc cx
	jmp lop3
	
p1:call search_shop12
	mov [si+18],cx
	add di,20
	cmp di,dx
	jge quit4
	jmp lop4
	
	
quit4:	
	pop dx
	pop cx
	pop bx
	pop ax
ret;返回后需要返回至功能三的1
fun4 endp
	

	
	
	
	
	
	
	
	
	
	

;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：输出商店1与2中某商品的信息。
;入口参数：shop1中该商品的地址di，shop2中该商品的地址si。
;出口参数：无。

print_product proc
;输出商店1中对应商品的信息
	write output
    write crlf
	write output1
	write crlf
    write in_product+2
	write crlf
	write op1
	mov ax,[di+10]
	mov dx,16
	call f2t10
	write crlf
	write op2
	mov ax,[di+12]
	mov dx,16
	call f2t10
	write crlf
	write op3
	mov ax,[di+14]
	mov dx,16
	call f2t10
	write crlf
	write op4
	mov ax,[di+16]
	mov dx,16
	call f2t10
	call search_shop12
	
	;输出商店2中对应商品的信息
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
	
	
	

;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：在shop1中查找与用户输入对应的商品。
;(若未能在指定网店中找到该商品，重新提示输入网店名称和商品名称。若只输入回车，返回标记。)
;入口参数：无。
;出口参数：shop1中商品的地址di,标记位symble(1 is true.-1 is false)。
search_product proc
	push ax
	push bx
	push cx
	push dx
	
l8:	write crlf
	write buf5
	read in_product
	write crlf
	cmp in_product[1],0
	je err2 
	jmp l9
err2:mov [symble],-1	;只输入了回车，返回功能三的1
	jmp quit1

;search the product
l9: mov di,offset s1
	add di,6          ;第一个商店第一个商品的地址
	mov bl,[in_product+1]         ;偏移地址
	mov bh,0
	mov si,offset in_product
	cmp bx,10
	je next33
	mov dl,[di+bx]  ;防止输入商品名为内置商品名的子集时也搜索成功
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
	
;if the char is same
l10:cmp bx,1
	je l12          ;find the product
	dec bx
	jmp next33

;if the char is different
l11:
	add di,20
	mov bl,[in_product+1]
	mov bh,0
	mov cl,[flag]
	cmp cl,1
	je q1
	jmp q2
q1:
	mov cx,offset s2
	cmp cx,di
	je l8      ;fail to search,repeat to input
	jmp q3
q2:	mov cx,offset s2
	cmp cx,di
	je l8      ;fail to search,repeat to input
	jmp q3
q3: jmp next33
	
l12	:
	mov [symble],1    ;找到商品的地址，返回正确的标记值。
	jmp quit1
quit1:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
	
search_product endp
	
	

	
;编写者：潘许飞。
;同组同学：潘璐。
;函数功能：在shop2中查找与shop1对应的商品。
;入口参数：shop1中商品的地址di。
;出口参数：shop2中商品的地址si。
search_shop12 proc
	push ax
	push bx
	push cx
	
;search_shop12 the product
s15:mov si,offset gb1
	mov bx,10
	jmp snext
snext:
	mov ch,[si+bx-1]
	mov cl,[di+bx-1]
	cmp ch,cl
	jne s17
	jmp s16
	
	
;if the char is same
s16:cmp bx,1
	je s19         ;find the product
	dec bx
	jmp snext

;if the char is different
s17:
	add si,20
	mov bx,10
	jmp snext
	
s19:
	pop cx
	pop bx
	pop ax
	ret;返回后需要返回至功能三的1
search_shop12 endp






radix proc
		push cx
		push edx
		xor cx,cx
lop1:	xor edx,edx
		div ebx
		push dx
		inc cx
		or eax,eax
		jnz lop1
lop2:	pop ax
		cmp al,10
		jb r1
		add al,7
r1:		add al,30h
		mov [si],al
		inc si
		loop lop2
		pop edx
		pop cx
		ret
radix endp



f2t10 proc far
		push ebx
		push si
		lea si,buf0
		cmp dx,32
		je b
		movsx eax,ax
b:		or eax,eax
		jns plus
		neg eax
		mov byte ptr[si],'-'
		inc si
plus:	mov ebx,10
		call radix
		mov byte ptr[si],'$'
		lea dx,buf0
		mov ah,9
		int 21h
		pop si
		pop ebx
		ret
f2t10 endp




		
	
		
f10t2 proc far
      push ebx
	  mov eax,0
	  mov sign,0
	  mov bl,[si]
	  cmp bl,'+'
	  je f10
	  cmp bl,'-'
	  jne next8
	  mov sign,1
f10:dec cx
    jz err
next7:inc si
      mov bl,[si]
next8:cmp bl,'0'
      jb err
	  cmp bl,'9'
	  ja err
	  sub bl,30h
	  movzx ebx,bl
	  imul eax,10
	  jo err
	  add eax,ebx
	  jo err
	  js err
	  jc err
	  dec cx
	  jnz next7
	  cmp dx,16
	  jne pp0
	  cmp eax,7fffh
	  ja err
pp0:cmp sign,1
    jne qq
	neg eax
qq:pop ebx
   ret
err:mov si,-1
    jmp qq
f10t2 endp











		
code ends
end start
end l4
