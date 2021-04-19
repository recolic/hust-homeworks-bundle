.387
		PUBLIC	r_strlen_
		PUBLIC	r_streql_
		PUBLIC	r_getchar_
		PUBLIC	r_exit_
		PUBLIC	echo_
		PUBLIC	r_print_
		PUBLIC	readline_unsafe_
		PUBLIC	login_
		PUBLIC	show_secret_
		PUBLIC	show_secret_unlogin_
		PUBLIC	fake_main_
		PUBLIC	_user
		PUBLIC	_pswd
		PUBLIC	_shopA
		PUBLIC	_shopB
		EXTRN	__STK:BYTE
		EXTRN	_small_code_:BYTE
DGROUP		GROUP	CONST,CONST2,_DATA
_TEXT		SEGMENT	BYTE PUBLIC USE16 'CODE'
		ASSUME CS:_TEXT, DS:DGROUP, SS:DGROUP
r_strlen_:
    push        ax 
    mov         ax,4 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    mov         bx,ax 
    xor         ax,ax 
L$1:
    cmp         byte ptr [bx],0 
    je          L$2 
    inc         bx 
    inc         ax 
    jmp         L$1 
L$2:
    pop         bx 
    ret         
r_streql_:
    push        ax 
    mov         ax,6 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        si 
    mov         bx,ax 
    mov         si,dx 
L$3:
    mov         al,byte ptr [bx] 
    test        al,al 
    je          L$5 
    cmp         al,byte ptr [si] 
    je          L$4 
    xor         ax,ax 
    pop         si 
    pop         bx 
    ret         
L$4:
    inc         bx 
    inc         si 
    jmp         L$3 
L$5:
    cmp         byte ptr [si],0 
    jne         L$6 
    mov         ax,1 
    pop         si 
    pop         bx 
    ret         
L$6:
    xor         ah,ah 
    pop         si 
    pop         bx 
    ret         
L$7:
    mov         byte ptr -100H[bp+si],24H 
    nop         
    mov         sp,bp 
    pop         bp 
L$8:
    pop         di 
    pop         si 
L$9:
    pop         dx 
    pop         cx 
    pop         bx 
    ret         
r_getchar_:
    mov         ax,0cH 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    nop         
    mov         al,0aH 
    jmp         L$8 
r_exit_:
    mov         ax,0cH 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    nop         
    jmp         L$8 
echo_:
    push        ax 
    mov         ax,2 
    call        near ptr __STK 
    pop         ax 
    call        near ptr r_print_ 
    mov         ax,offset DGROUP:L$22 
r_print_:
    push        ax 
    mov         ax,10eH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    sub         sp,100H 
    mov         dx,ax 
    call        near ptr r_strlen_ 
    xor         si,si 
L$10:
    cmp         si,ax 
    jge         L$7 
    mov         bx,dx 
    add         bx,si 
    mov         bl,byte ptr [bx] 
    mov         byte ptr -100H[bp+si],bl 
    inc         si 
    jmp         L$10 
readline_unsafe_:
    push        ax 
    mov         ax,8 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    mov         cx,ax 
    xor         dx,dx 
L$11:
    call        near ptr r_getchar_ 
    cmp         al,0dH 
    je          L$12 
    cmp         al,0aH 
    je          L$12 
    mov         bx,cx 
    add         bx,dx 
    mov         byte ptr [bx],al 
    inc         dx 
    jmp         L$11 
L$12:
    mov         bx,cx 
    add         bx,dx 
    mov         byte ptr [bx],0 
    jmp         near ptr L$9 
login_:
    mov         ax,2cH 
    call        near ptr __STK 
    push        cx 
    push        dx 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    sub         sp,20H 
    mov         cx,10H 
    mov         ax,ds 
    mov         es,ax 
    lea         di,-20H[bp] 
    mov         si,offset DGROUP:L$27 
    rep movsw   
    mov         ax,offset DGROUP:L$23 
    call        near ptr r_print_ 
    lea         ax,-20H[bp] 
    call        near ptr readline_unsafe_ 
    mov         al,byte ptr -20H[bp] 
    test        al,al 
    jne         L$13 
    xor         ah,ah 
    jmp         L$17 
L$13:
    cmp         al,71H 
    jne         L$14 
    call        near ptr r_exit_ 
L$14:
    mov         dx,offset _user 
    lea         ax,-20H[bp] 
    call        near ptr r_streql_ 
    test        ax,ax 
    jne         L$16 
L$15:
    mov         ax,offset DGROUP:L$24 
    call        near ptr echo_ 
    xor         ax,ax 
    jmp         L$17 
L$16:
    mov         ax,offset DGROUP:L$25 
    call        near ptr r_print_ 
    lea         ax,-20H[bp] 
    call        near ptr readline_unsafe_ 
    mov         dx,offset _pswd 
    lea         ax,-20H[bp] 
    call        near ptr r_streql_ 
    test        ax,ax 
    je          L$15 
    mov         ax,offset DGROUP:L$26 
    call        near ptr echo_ 
    mov         ax,1 
L$17:
    mov         sp,bp 
    pop         bp 
    pop         di 
    pop         si 
    pop         dx 
    pop         cx 
    ret         
show_secret_:
    mov         ax,2 
    jmp         near ptr __STK 
show_secret_unlogin_:
    mov         ax,2 
    jmp         near ptr __STK 
fake_main_:
    mov         ax,4 
    call        near ptr __STK 
    push        dx 
    xor         dx,dx 
    jmp         L$19 
L$18:
    inc         dx 
    cmp         dx,3 
    jge         L$20 
L$19:
    call        near ptr login_ 
    test        ax,ax 
    je          L$18 
    call        near ptr show_secret_ 
    jmp         L$21 
L$20:
    call        near ptr show_secret_unlogin_ 
L$21:
    xor         ax,ax 
    pop         dx 
    ret         
_TEXT		ENDS
CONST		SEGMENT	WORD PUBLIC USE16 'DATA'
L$22:
    DB	0dH, 0aH, 0
L$23:
    DB	59H, 6fH, 75H, 72H, 20H, 6eH, 61H, 6dH
    DB	65H, 20H, 70H, 6cH, 65H, 61H, 73H, 65H
    DB	3aH, 20H, 0
L$24:
    DB	50H, 65H, 72H, 6dH, 69H, 73H, 73H, 69H
    DB	6fH, 6eH, 20H, 64H, 65H, 6eH, 69H, 65H
    DB	64H, 2eH, 0
L$25:
    DB	59H, 6fH, 75H, 72H, 20H, 70H, 61H, 73H
    DB	73H, 77H, 6fH, 72H, 64H, 20H, 70H, 6cH
    DB	65H, 61H, 73H, 65H, 3aH, 20H, 0
L$26:
    DB	50H, 61H, 73H, 73H, 65H, 64H, 2eH, 0

CONST		ENDS
CONST2		SEGMENT	WORD PUBLIC USE16 'DATA'
CONST2		ENDS
_DATA		SEGMENT	WORD PUBLIC USE16 'DATA'
_user:
    DB	62H, 65H, 6eH, 73H, 6fH, 6eH, 67H, 20H
    DB	6cH, 69H, 75H, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
_pswd:
    DB	74H, 65H, 73H, 74H, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
_shopA:
    DB	53H, 48H, 4fH, 50H, 31H, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
_shopB:
    DB	53H, 48H, 4fH, 50H, 32H, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
L$27:
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0

_DATA		ENDS
		END
