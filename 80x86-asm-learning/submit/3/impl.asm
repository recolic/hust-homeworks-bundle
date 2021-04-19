.387
		PUBLIC	func3_fill_profit_table_
		PUBLIC	func4_fill_rank_table_
		PUBLIC	profit_mark_of_
		PUBLIC	search_product_
		EXTRN	__STK:BYTE
		EXTRN	_output_price:BYTE
		EXTRN	_input_price:BYTE
		EXTRN	FIDRQQ:BYTE
		EXTRN	_profit_table:BYTE
		EXTRN	FIWRQQ:BYTE
		EXTRN	_rank_table:BYTE
		EXTRN	_products_name:BYTE
		EXTRN	strcmp_:BYTE
		EXTRN	__8087:BYTE
		EXTRN	__init_87_emulator:BYTE
		EXTRN	_small_code_:BYTE
DGROUP		GROUP	CONST,CONST2,_DATA
_TEXT		SEGMENT	BYTE PUBLIC USE16 'CODE'
		ASSUME CS:_TEXT, DS:DGROUP, SS:DGROUP
func3_fill_profit_table_:
    mov         ax,0cH 
    call        near ptr __STK 
    push        bx 
    push        dx 
    push        si 
    push        bp 
    mov         bp,sp 
    sub         sp,2 
    xor         bx,bx 
tmp1:
    mov         si,bx 
    shl         si,1 
    mov         ax,word ptr _output_price[si] 
    cwd         
    idiv        word ptr _input_price[si] 
    dec         ax 
    mov         word ptr -2[bp],ax 
    fild        word ptr -2[bp] 
    mov         si,bx 
    shl         si,1 
    shl         si,1 
    fstp        dword ptr _profit_table[si] 
    inc         bx 
    nop         
    fwait       
    cmp         bx,3 
    jl          tmp1 
    mov         sp,bp 
    pop         bp 
    pop         si 
    pop         dx 
    pop         bx 
    ret         
func4_fill_rank_table_:
    mov         ax,0eH 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        bp 
    mov         bp,sp 
    sub         sp,2 
    xor         cx,cx 
    jmp         tmp3 
tmp2:
    inc         cx 
    cmp         cx,3 
    jge         tmp6 
tmp3:
    mov         bx,cx 
    shl         bx,1 
    mov         word ptr _rank_table[bx],1 
    xor         dx,dx 
    jmp         tmp5 
tmp4:
    inc         dx 
    cmp         dx,3 
    jge         tmp2 
tmp5:
    mov         bx,cx 
    shl         bx,1 
    shl         bx,1 
    mov         si,dx 
    shl         si,1 
    shl         si,1 
    fld         dword ptr _profit_table[bx] 
    fcomp       dword ptr _profit_table[si] 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jae         tmp4 
    mov         bx,cx 
    shl         bx,1 
    inc         word ptr _rank_table[bx] 
    jmp         tmp4 
tmp6:
    mov         sp,bp 
    pop         bp 
tmp7:
    pop         si 
    pop         dx 
    pop         cx 
    pop         bx 
    ret         
profit_mark_of_:
    push        ax 
    mov         ax,18H 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        dx 
    push        bp 
    mov         bp,sp 
    sub         sp,10H 
    mov         bx,ax 
    shl         bx,1 
    mov         ax,word ptr _output_price[bx] 
    cwd         
    idiv        word ptr _input_price[bx] 
    dec         ax 
    mov         word ptr -4[bp],ax 
    fild        word ptr -4[bp] 
    fstp        dword ptr -8[bp] 
    fldz        
    fcomp       dword ptr -8[bp] 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp8 
    mov         al,46H 
    jmp         tmp12 
tmp8:
    fld         dword ptr -8[bp] 
    fst         qword ptr -10H[bp] 
    fcomp       qword ptr DGROUP:tmp16 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp9 
    mov         al,41H 
    jmp         tmp12 
tmp9:
    fld         qword ptr -10H[bp] 
    fcomp       qword ptr DGROUP:tmp17 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp10 
    mov         al,42H 
    jmp         tmp12 
tmp10:
    fld         qword ptr -10H[bp] 
    fcomp       qword ptr DGROUP:tmp18 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp11 
    mov         al,43H 
    jmp         tmp12 
tmp11:
    mov         al,44H 
tmp12:
    mov         sp,bp 
    pop         bp 
    pop         dx 
    pop         bx 
    ret         
search_product_:
    push        ax 
    mov         ax,0aH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    mov         si,ax 
    xor         bx,bx 
    mov         cl,5 
    jmp         tmp14 
tmp13:
    inc         bx 
    cmp         bx,3 
    jge         tmp15 
tmp14:
    mov         dx,bx 
    shl         dx,cl 
    add         dx,offset _products_name 
    mov         ax,si 
    call        near ptr strcmp_ 
    test        ax,ax 
    jne         tmp13 
    mov         ax,bx 
    jmp         near ptr tmp7 
tmp15:
    mov         ax,0ffffH 
    jmp         near ptr tmp7 
_TEXT		ENDS
CONST		SEGMENT	WORD PUBLIC USE16 'DATA'
tmp16:
    DB	0cdH, 0ccH, 0ccH, 0ccH, 0ccH, 0ccH, 0ecH, 3fH
tmp17:
    DB	0, 0, 0, 0, 0, 0, 0e0H, 3fH
tmp18:
    DB	9aH, 99H, 99H, 99H, 99H, 99H, 0c9H, 3fH

CONST		ENDS
CONST2		SEGMENT	WORD PUBLIC USE16 'DATA'
CONST2		ENDS
_DATA		SEGMENT	WORD PUBLIC USE16 'DATA'
_DATA		ENDS
		END
