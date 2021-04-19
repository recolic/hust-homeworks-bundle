.387
		PUBLIC	echo_
		PUBLIC	readline_unsafe_
		PUBLIC	login_
		PUBLIC	func1_ls_
		PUBLIC	func2_edit_
		PUBLIC	func5_print_profit_and_rank_
		PUBLIC	func6_exit_
		PUBLIC	main_
		PUBLIC	_user
		PUBLIC	_pswd
		PUBLIC	_shopA
		PUBLIC	_shopB
		PUBLIC	_products_name
		PUBLIC	_input_price
		PUBLIC	_output_price
		PUBLIC	_profit_table
		PUBLIC	_rank_table
		PUBLIC	_logged_in
		EXTRN	__STK:BYTE
		EXTRN	printf_:BYTE
		EXTRN	___iob:BYTE
		EXTRN	fgetc_:BYTE
		EXTRN	exit_:BYTE
		EXTRN	strcmp_:BYTE
		EXTRN	scanf_:BYTE
		EXTRN	search_product_:BYTE
		EXTRN	profit_mark_of_:BYTE
		EXTRN	func3_fill_profit_table_:BYTE
		EXTRN	func4_fill_rank_table_:BYTE
		EXTRN	_small_code_:BYTE
		EXTRN	_cstart_:BYTE
DGROUP		GROUP	CONST,CONST2,_DATA
_TEXT		SEGMENT	BYTE PUBLIC USE16 'CODE'
		ASSUME CS:_TEXT, DS:DGROUP, SS:DGROUP
echo_:
    push        ax 
    mov         ax,6 
    call        near ptr __STK 
    pop         ax 
    push        ax 
    mov         ax,offset DGROUP:L$23 
    push        ax 
    call        near ptr printf_ 
    add         sp,4 
    ret         
readline_unsafe_:
    push        ax 
    mov         ax,0aH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    mov         cx,ax 
    xor         dx,dx 
L$1:
    cmp         word ptr ___iob+2,0 
    jle         L$2 
    mov         bx,word ptr ___iob 
    mov         al,byte ptr [bx] 
    xor         ah,ah 
    sub         ax,0dH 
    cmp         ax,0dH 
    ja          L$3 
L$2:
    mov         ax,offset ___iob 
    call        near ptr fgetc_ 
    jmp         L$4 
L$3:
    dec         word ptr ___iob+2 
    lea         ax,1[bx] 
    mov         word ptr ___iob,ax 
    mov         al,byte ptr [bx] 
    xor         ah,ah 
L$4:
    mov         bx,ax 
    cmp         bl,0dH 
    je          L$5 
    cmp         bl,0aH 
    je          L$5 
    mov         si,cx 
    add         si,dx 
    mov         byte ptr [si],bl 
    inc         dx 
    jmp         L$1 
L$5:
    mov         bx,cx 
    add         bx,dx 
    mov         byte ptr [bx],0 
    pop         si 
L$6:
    pop         dx 
    pop         cx 
    pop         bx 
    ret         
login_:
    mov         ax,2eH 
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
    mov         si,offset DGROUP:L$42 
    rep movsw   
L$7:
    mov         ax,offset DGROUP:L$24 
    push        ax 
    call        near ptr printf_ 
    add         sp,2 
    lea         ax,-20H[bp] 
    call        near ptr readline_unsafe_ 
    mov         al,byte ptr -20H[bp] 
    test        al,al 
    je          L$7 
    cmp         al,71H 
    jne         L$8 
    xor         ax,ax 
    call        near ptr exit_ 
L$8:
    mov         dx,offset _user 
    lea         ax,-20H[bp] 
    call        near ptr strcmp_ 
    test        ax,ax 
    je          L$10 
L$9:
    mov         ax,offset DGROUP:L$25 
    call        near ptr echo_ 
    jmp         L$7 
L$10:
    mov         ax,offset DGROUP:L$26 
    push        ax 
    call        near ptr printf_ 
    add         sp,2 
    lea         ax,-20H[bp] 
    call        near ptr readline_unsafe_ 
    mov         dx,offset _pswd 
    lea         ax,-20H[bp] 
    call        near ptr strcmp_ 
    test        ax,ax 
    jne         L$9 
    mov         ax,offset DGROUP:L$27 
    call        near ptr echo_ 
    mov         ax,1 
    mov         sp,bp 
    pop         bp 
    pop         di 
    pop         si 
    pop         dx 
    pop         cx 
    ret         
func1_ls_:
    mov         ax,10H 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    xor         dx,dx 
    mov         cl,5 
L$11:
    mov         bx,dx 
    shl         bx,1 
    push        word ptr _output_price[bx] 
    push        word ptr _input_price[bx] 
    mov         bx,dx 
    shl         bx,cl 
    add         bx,offset _products_name 
    push        bx 
    mov         bx,offset DGROUP:L$28 
    push        bx 
    call        near ptr printf_ 
    add         sp,8 
    inc         dx 
    cmp         dx,3 
    jl          L$11 
    jmp         near ptr L$6 
func2_edit_:
    mov         ax,32H 
    call        near ptr __STK 
    push        bx 
    push        bp 
    mov         bp,sp 
    sub         sp,24H 
    mov         ax,offset DGROUP:L$29 
    call        near ptr echo_ 
    lea         ax,-2[bp] 
    push        ax 
    lea         ax,-4[bp] 
    push        ax 
    lea         ax,-24H[bp] 
    push        ax 
    mov         ax,offset DGROUP:L$30 
    push        ax 
    call        near ptr scanf_ 
    add         sp,8 
    lea         ax,-24H[bp] 
    call        near ptr search_product_ 
    cmp         ax,0ffffH 
    jne         L$12 
    mov         ax,offset DGROUP:L$31 
    jmp         L$13 
L$12:
    mov         bx,ax 
    shl         bx,1 
    mov         ax,word ptr -4[bp] 
    mov         word ptr _input_price[bx],ax 
    mov         ax,word ptr -2[bp] 
    mov         word ptr _output_price[bx],ax 
    mov         ax,offset DGROUP:L$32 
L$13:
    call        near ptr echo_ 
    mov         sp,bp 
    pop         bp 
    pop         bx 
    ret         
func5_print_profit_and_rank_:
    mov         ax,10H 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    xor         dx,dx 
    mov         cl,5 
L$14:
    mov         bx,dx 
    shl         bx,1 
    push        word ptr _rank_table[bx] 
    mov         ax,dx 
    call        near ptr profit_mark_of_ 
    xor         ah,ah 
    push        ax 
    mov         ax,dx 
    shl         ax,cl 
    add         ax,offset _products_name 
    push        ax 
    mov         ax,offset DGROUP:L$33 
    push        ax 
    call        near ptr printf_ 
    add         sp,8 
    inc         dx 
    cmp         dx,3 
    jl          L$14 
    jmp         near ptr L$6 
func6_exit_:
    mov         ax,2 
    call        near ptr __STK 
    xor         ax,ax 
    jmp         near ptr exit_ 
L$15:
    DW	offset L$17
    DW	offset L$18
    DW	offset L$19
    DW	offset L$20
    DW	offset L$21
    DW	offset L$22
main_:
    mov         ax,18H 
    call        near ptr __STK 
    push        bx 
    push        bp 
    mov         bp,sp 
    sub         sp,10H 
    call        near ptr login_ 
L$16:
    mov         ax,offset DGROUP:L$34 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$35 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$36 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$37 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$38 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$39 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$40 
    call        near ptr echo_ 
    mov         ax,offset DGROUP:L$41 
    push        ax 
    call        near ptr printf_ 
    add         sp,2 
    lea         ax,-10H[bp] 
    call        near ptr readline_unsafe_ 
    mov         al,byte ptr -10H[bp] 
    sub         al,31H 
    cmp         al,5 
    ja          L$16 
    xor         ah,ah 
    mov         bx,ax 
    shl         bx,1 
    jmp         word ptr cs:L$15[bx] 
L$17:
    call        near ptr func1_ls_ 
    jmp         L$16 
L$18:
    call        near ptr func2_edit_ 
    jmp         L$16 
L$19:
    call        near ptr func3_fill_profit_table_ 
    jmp         L$16 
L$20:
    call        near ptr func4_fill_rank_table_ 
    jmp         L$16 
L$21:
    call        near ptr func5_print_profit_and_rank_ 
    jmp         L$16 
L$22:
    call        near ptr func6_exit_ 
    jmp         L$16 
_TEXT		ENDS
CONST		SEGMENT	WORD PUBLIC USE16 'DATA'
L$23:
    DB	25H, 73H, 0dH, 0aH, 0
L$24:
    DB	59H, 6fH, 75H, 72H, 20H, 6eH, 61H, 6dH
    DB	65H, 20H, 70H, 6cH, 65H, 61H, 73H, 65H
    DB	3aH, 20H, 0
L$25:
    DB	50H, 65H, 72H, 6dH, 69H, 73H, 73H, 69H
    DB	6fH, 6eH, 20H, 64H, 65H, 6eH, 69H, 65H
    DB	64H, 2eH, 0
L$26:
    DB	59H, 6fH, 75H, 72H, 20H, 70H, 61H, 73H
    DB	73H, 77H, 6fH, 72H, 64H, 20H, 70H, 6cH
    DB	65H, 61H, 73H, 65H, 3aH, 20H, 0
L$27:
    DB	50H, 61H, 73H, 73H, 65H, 64H, 2eH, 0
L$28:
    DB	25H, 73H, 20H, 3eH, 20H, 49H, 6eH, 70H
    DB	75H, 74H, 50H, 72H, 69H, 63H, 65H, 20H
    DB	25H, 64H, 20H, 4fH, 75H, 74H, 70H, 75H
    DB	74H, 50H, 72H, 69H, 63H, 65H, 20H, 25H
    DB	64H, 2eH, 0dH, 0aH, 0
L$29:
    DB	47H, 69H, 76H, 65H, 20H, 60H, 24H, 6eH
    DB	61H, 6dH, 65H, 20H, 24H, 69H, 6eH, 70H
    DB	75H, 74H, 50H, 72H, 69H, 63H, 65H, 20H
    DB	24H, 6fH, 75H, 74H, 70H, 75H, 74H, 50H
    DB	72H, 69H, 63H, 65H, 60H, 20H, 70H, 6cH
    DB	65H, 61H, 73H, 65H, 2eH, 0
L$30:
    DB	25H, 73H, 20H, 25H, 64H, 20H, 25H, 64H
    DB	0
L$31:
    DB	4eH, 6fH, 74H, 20H, 66H, 6fH, 75H, 6eH
    DB	64H, 20H, 65H, 72H, 72H, 6fH, 72H, 2eH
    DB	0
L$32:
    DB	44H, 6fH, 6eH, 65H, 2eH, 0
L$33:
    DB	25H, 73H, 3aH, 20H, 70H, 72H, 6fH, 66H
    DB	69H, 74H, 20H, 6dH, 61H, 72H, 6bH, 20H
    DB	25H, 63H, 20H, 72H, 61H, 6eH, 6bH, 20H
    DB	25H, 64H, 0dH, 0aH, 0
L$34:
    DB	0
L$35:
    DB	66H, 75H, 6eH, 63H, 31H, 5fH, 6cH, 73H
    DB	0
L$36:
    DB	66H, 75H, 6eH, 63H, 32H, 5fH, 65H, 64H
    DB	69H, 74H, 0
L$37:
    DB	66H, 75H, 6eH, 63H, 33H, 5fH, 63H, 61H
    DB	6cH, 63H, 5fH, 70H, 72H, 6fH, 66H, 69H
    DB	74H, 0
L$38:
    DB	66H, 75H, 6eH, 63H, 34H, 5fH, 63H, 61H
    DB	6cH, 63H, 5fH, 72H, 61H, 6eH, 6bH, 20H
    DB	28H, 64H, 65H, 70H, 65H, 6eH, 64H, 3aH
    DB	20H, 66H, 75H, 6eH, 63H, 33H, 29H, 0
L$39:
    DB	66H, 75H, 6eH, 63H, 35H, 5fH, 70H, 72H
    DB	69H, 6eH, 74H, 5fH, 70H, 72H, 6fH, 66H
    DB	69H, 74H, 5fH, 61H, 6eH, 64H, 5fH, 72H
    DB	61H, 6eH, 6bH, 20H, 28H, 64H, 65H, 70H
    DB	65H, 6eH, 64H, 3aH, 20H, 66H, 75H, 6eH
    DB	63H, 34H, 29H, 0
L$40:
    DB	66H, 75H, 6eH, 63H, 36H, 5fH, 65H, 78H
    DB	69H, 74H, 0
L$41:
    DB	20H, 31H, 2dH, 36H, 20H, 3fH, 20H, 0

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
_products_name:
    DB	70H, 65H, 6eH, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	62H, 6fH, 6fH, 6bH, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	73H, 63H, 61H, 6cH, 61H, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
_input_price:
    DB	23H, 0, 16H, 0, 3dH, 0
_output_price:
    DB	0bH, 0, 1cH, 0, 0e8H, 3
_profit_table:
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0
_rank_table:
    DB	0ffH, 0ffH, 0ffH, 0ffH, 0ffH, 0ffH
_logged_in:
    DB	0, 0
L$42:
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0

_DATA		ENDS
		END
