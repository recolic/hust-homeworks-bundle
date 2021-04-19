.387
		PUBLIC	fake_main_
		EXTRN	__STK:BYTE
		EXTRN	__U4D:BYTE
		EXTRN	__U4M:BYTE
		EXTRN	__I8DQ:BYTE
		EXTRN	__I8DR:BYTE
		EXTRN	FIDRQQ:BYTE
		EXTRN	FIWRQQ:BYTE
		EXTRN	__8087:BYTE
		EXTRN	__init_87_emulator:BYTE
		EXTRN	_small_code_:BYTE
DGROUP		GROUP	CONST,CONST2,_DATA
_TEXT		SEGMENT	BYTE PUBLIC USE16 'CODE'
		ASSUME CS:_TEXT, DS:DGROUP, SS:DGROUP
r_hash_:
    push        ax 
    mov         ax,0aH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        si 
    push        di 
    mov         bx,ax 
    mov         di,8bfH 
    mov         si,131H 
tmp1:
    mov         al,byte ptr [bx] 
    test        al,al 
    je          tmp4 
    xor         ah,ah 
    mov         cx,ax 
    and         cl,0fH 
    xor         dx,dx 
    jcxz        tmp3 
tmp2:
    shl         ax,1 
    rcl         dx,1 
    loop        tmp2 
tmp3:
    add         di,ax 
    adc         si,dx 
    inc         bx 
    jmp         tmp1 
tmp4:
    mov         ax,di 
    mov         dx,si 
tmp5:
    pop         di 
    pop         si 
    pop         cx 
    pop         bx 
    ret         
meg_mod_:
    push        ax 
    mov         ax,4 
    call        near ptr __STK 
    pop         ax 
    push        bp 
    mov         bp,sp 
    xor         ax,ax 
    pop         bp 
    ret         2 
naive_mod_:
    push        ax 
    mov         ax,12H 
    call        near ptr __STK 
    pop         ax 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    sub         sp,4 
    push        ax 
    mov         di,dx 
    mov         word ptr -4[bp],bx 
    mov         word ptr -2[bp],cx 
    xor         si,si 
    cmp         word ptr 0aH[bp],0 
    jne         tmp8 
    cmp         word ptr 8[bp],2710H 
    jae         tmp8 
    mov         ax,bx 
    mov         dx,cx 
    mov         bx,word ptr -6[bp] 
    mov         cx,di 
    call        near ptr __U4D 
tmp6:
    mov         ax,si 
    cwd         
    cmp         dx,word ptr 0aH[bp] 
    jb          tmp7 
    jne         tmp9 
    cmp         ax,word ptr 8[bp] 
    jae         tmp9 
tmp7:
    mov         ax,bx 
    mov         dx,cx 
    mov         bx,word ptr -4[bp] 
    mov         cx,word ptr -2[bp] 
    call        near ptr __U4M 
    mov         bx,word ptr -6[bp] 
    mov         cx,di 
    call        near ptr __U4D 
    inc         si 
    jmp         tmp6 
tmp8:
    mov         ax,word ptr 8[bp] 
    mov         dx,word ptr 0aH[bp] 
    shr         dx,1 
    rcr         ax,1 
    push        dx 
    push        ax 
    mov         ax,word ptr -6[bp] 
    mov         dx,di 
    call        near ptr naive_mod_ 
    mov         bx,ax 
    mov         cx,dx 
    call        near ptr __U4M 
    mov         bx,word ptr -6[bp] 
    mov         cx,di 
    call        near ptr __U4D 
    test        byte ptr 8[bp],1 
    je          tmp9 
    mov         ax,bx 
    mov         dx,cx 
    mov         bx,word ptr -4[bp] 
    mov         cx,word ptr -2[bp] 
    call        near ptr __U4M 
    mov         bx,word ptr -6[bp] 
    mov         cx,di 
    call        near ptr __U4D 
tmp9:
    mov         ax,bx 
    mov         dx,cx 
    mov         sp,bp 
    pop         bp 
    pop         di 
    pop         si 
    ret         4 
fake_verify_:
    push        ax 
    mov         ax,14H 
    call        near ptr __STK 
    pop         ax 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    push        ax 
    push        dx 
    push        bx 
    push        cx 
    xor         si,si 
    jmp         tmp11 
tmp10:
    inc         si 
    cmp         si,20H 
    jge         tmp14 
tmp11:
    mov         bx,word ptr -2[bp] 
    add         bx,si 
    mov         al,byte ptr [bx] 
    xor         ah,ah 
    mov         cx,ax 
    xor         di,di 
    test        ax,ax 
    jne         tmp12 
    mov         bx,si 
    shl         bx,1 
    shl         bx,1 
    add         bx,word ptr -4[bp] 
    mov         ax,word ptr 2[bx] 
    or          ax,word ptr [bx] 
    je          tmp14 
tmp12:
    mov         ax,word ptr -6[bp] 
    cwd         
    push        dx 
    push        ax 
    mov         ax,word ptr -8[bp] 
    cwd         
    mov         bx,cx 
    mov         cx,di 
    call        near ptr naive_mod_ 
    mov         bx,si 
    shl         bx,1 
    shl         bx,1 
    add         bx,word ptr -4[bp] 
    cmp         dx,word ptr 2[bx] 
    jne         tmp13 
    cmp         ax,word ptr [bx] 
    je          tmp10 
tmp13:
    xor         ax,ax 
    jmp         tmp15 
tmp14:
    mov         ax,1 
tmp15:
    mov         sp,bp 
    pop         bp 
    pop         di 
    pop         si 
    ret         
r_print_2d_:
    push        ax 
    mov         ax,12H 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    sub         sp,4 
    mov         cx,ax 
    mov         ax,ds 
    mov         es,ax 
    lea         di,-4[bp] 
    mov         si,offset DGROUP:tmp75 
    movsw       
    movsb       
    mov         bx,0aH 
    mov         ax,cx 
    cwd         
    idiv        bx 
    cwd         
    idiv        bx 
    add         dx,30H 
    mov         byte ptr -4[bp],dl 
    mov         ax,cx 
    cwd         
    idiv        bx 
    add         dx,30H 
    mov         byte ptr -3[bp],dl 
    lea         ax,-4[bp] 
    call        near ptr r_print_ 
tmp16:
    mov         sp,bp 
    pop         bp 
tmp17:
    pop         di 
    pop         si 
tmp18:
    pop         dx 
    pop         cx 
tmp19:
    pop         bx 
    ret         
r_print_long_:
    push        ax 
    mov         ax,1cH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    sub         sp,0cH 
    push        ax 
    push        dx 
    mov         ax,ds 
    mov         es,ax 
    lea         di,-0cH[bp] 
    mov         si,offset DGROUP:tmp76 
    movsw       
    movsw       
    movsw       
    movsw       
    movsw       
    movsw       
    lea         di,-0cH[bp] 
    xor         ax,ax 
    xor         bx,bx 
    mov         cx,dx 
    mov         dx,word ptr -0eH[bp] 
    mov         si,offset DGROUP:tmp56 
    call        near ptr __I8DQ 
    mov         si,offset DGROUP:tmp57 
    call        near ptr __I8DR 
    add         dx,30H 
    adc         cx,0 
    adc         bx,0 
    mov         byte ptr -0cH[bp],dl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,0ca00H 
    mov         cx,3b9aH 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -0bH[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,0e100H 
    mov         cx,5f5H 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -0aH[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,9680H 
    mov         cx,98H 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -9[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,4240H 
    mov         cx,0fH 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -8[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,86a0H 
    mov         cx,1 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -7[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,2710H 
    xor         cx,cx 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -6[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,3e8H 
    xor         cx,cx 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -5[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,64H 
    xor         cx,cx 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -4[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -3[bp],bl 
    mov         ax,word ptr -0eH[bp] 
    mov         dx,word ptr -10H[bp] 
    mov         bx,0aH 
    xor         cx,cx 
    call        near ptr __U4D 
    add         bx,30H 
    mov         byte ptr -2[bp],bl 
tmp20:
    cmp         byte ptr [di],30H 
    jne         tmp21 
    inc         di 
    jmp         tmp20 
tmp21:
    mov         ax,di 
    call        near ptr r_print_ 
    mov         sp,bp 
    pop         bp 
    jmp         near ptr tmp5 
r_strlen_:
    push        ax 
    mov         ax,4 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    mov         bx,ax 
    xor         ax,ax 
tmp22:
    cmp         byte ptr [bx],0 
    jne         tmp23 
    jmp         near ptr tmp19 
tmp23:
    inc         bx 
    inc         ax 
    jmp         tmp22 
r_streql_:
    push        ax 
    mov         ax,6 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        si 
    mov         bx,ax 
    mov         si,dx 
tmp24:
    mov         al,byte ptr [bx] 
    test        al,al 
    je          tmp26 
    cmp         al,byte ptr [si] 
    je          tmp25 
    xor         ax,ax 
    pop         si 
    pop         bx 
    ret         
tmp25:
    inc         bx 
    inc         si 
    jmp         tmp24 
tmp26:
    cmp         byte ptr [si],0 
    jne         tmp27 
    mov         ax,1 
    pop         si 
    pop         bx 
    ret         
tmp27:
    xor         ah,ah 
    pop         si 
    pop         bx 
    ret         
tmp28:
    mov         byte ptr -100H[bp+si],24H 
    lea         ax,-100H[bp] 
    push        dx 
    mov         dx,ax 
    mov         ah,9 
    int         21H 
    pop         dx 
    jmp         near ptr tmp16 
r_noecho_getchar_:
    mov         ax,0cH 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    mov         ah,8 
    int         21H 
tmp29:
    jmp         near ptr tmp17 
r_getchar_:
    mov         ax,0cH 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    mov         ah,1 
    int         21H 
    jmp         tmp29 
r_exit_:
    mov         ax,0cH 
    call        near ptr __STK 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    mov         ah,4cH 
    xor         al,al 
    int         21H 
    jmp         near ptr tmp17 
echo_:
    push        ax 
    mov         ax,2 
    call        near ptr __STK 
    pop         ax 
    call        near ptr r_print_ 
    mov         ax,offset DGROUP:tmp58 
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
tmp30:
    cmp         si,ax 
    jge         tmp28 
    mov         bx,dx 
    add         bx,si 
    mov         bl,byte ptr [bx] 
    mov         byte ptr -100H[bp+si],bl 
    inc         si 
    jmp         tmp30 
noecho_readline_unsafe_:
    push        ax 
    mov         ax,8 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    mov         cx,ax 
    xor         dx,dx 
tmp31:
    call        near ptr r_noecho_getchar_ 
    cmp         al,0dH 
    je          tmp32 
    cmp         al,0aH 
    je          tmp32 
    mov         bx,cx 
    add         bx,dx 
    mov         byte ptr [bx],al 
    inc         dx 
    jmp         tmp31 
tmp32:
    mov         bx,cx 
    add         bx,dx 
    mov         byte ptr [bx],0 
    jmp         near ptr tmp18 
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
tmp33:
    call        near ptr r_getchar_ 
    cmp         al,0dH 
    je          tmp32 
    cmp         al,0aH 
    je          tmp32 
    mov         bx,cx 
    add         bx,dx 
    mov         byte ptr [bx],al 
    inc         dx 
    jmp         tmp33 
decrypt_prices_:
    push        ax 
    mov         ax,8 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    call        near ptr r_hash_ 
    mov         cx,dx 
    mov         dx,ax 
    xor         ax,ax 
tmp34:
    mov         bx,ax 
    shl         bx,1 
    shl         bx,1 
    xor         word ptr _input_price[bx],dx 
    xor         word ptr _input_price+2[bx],cx 
    xor         word ptr _output_price[bx],dx 
    xor         word ptr _output_price+2[bx],cx 
    inc         ax 
    cmp         ax,3 
    jl          tmp34 
    jmp         near ptr tmp18 
login_:
    mov         ax,2eH 
    call        near ptr __STK 
    push        bx 
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
    mov         si,offset DGROUP:tmp77 
    rep movsw   
    mov         ax,offset DGROUP:tmp59 
    call        near ptr r_print_ 
    lea         ax,-20H[bp] 
    call        near ptr readline_unsafe_ 
    mov         al,byte ptr -20H[bp] 
    test        al,al 
    jne         tmp35 
    xor         ah,ah 
    jmp         near ptr tmp16 
tmp35:
    cmp         al,71H 
    jne         tmp36 
    call        near ptr r_exit_ 
tmp36:
    mov         dx,offset _user 
    lea         ax,-20H[bp] 
    call        near ptr r_streql_ 
    test        ax,ax 
    jne         tmp38 
tmp37:
    mov         ax,offset DGROUP:tmp60 
    call        near ptr echo_ 
    xor         ax,ax 
    jmp         near ptr tmp16 
tmp38:
    mov         ax,offset DGROUP:tmp61 
    call        near ptr r_print_ 
    lea         ax,-20H[bp] 
    call        near ptr noecho_readline_unsafe_ 
    mov         cx,word ptr _IllIllIl0OoOO00o 
    mov         bx,word ptr _llIlIIlIO0O0ooO0 
    mov         dx,offset _IllIlIlIOoOoOo0o 
    lea         ax,-20H[bp] 
    call        near ptr fake_verify_ 
    test        ax,ax 
    je          tmp37 
    mov         ax,offset DGROUP:tmp62 
    call        near ptr echo_ 
    lea         ax,-20H[bp] 
    call        near ptr decrypt_prices_ 
    mov         ax,offset DGROUP:tmp63 
    call        near ptr echo_ 
    mov         ax,1 
    jmp         near ptr tmp16 
profit_mark_of_:
    push        ax 
    mov         ax,1cH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        bp 
    mov         bp,sp 
    sub         sp,16H 
    mov         bx,ax 
    shl         bx,1 
    shl         bx,1 
    mov         ax,word ptr _output_price[bx] 
    mov         word ptr -0eH[bp],ax 
    mov         ax,word ptr _output_price+2[bx] 
    mov         word ptr -0cH[bp],ax 
    xor         ax,ax 
    mov         word ptr -0aH[bp],ax 
    mov         word ptr -8[bp],ax 
    fild        qword ptr -0eH[bp] 
    mov         ax,word ptr _input_price[bx] 
    mov         word ptr -0eH[bp],ax 
    mov         ax,word ptr _input_price+2[bx] 
    mov         word ptr -0cH[bp],ax 
    xor         ax,ax 
    mov         word ptr -0aH[bp],ax 
    mov         word ptr -8[bp],ax 
    fild        qword ptr -0eH[bp] 
    fdivp       st(1),st 
    fadd        dword ptr DGROUP:tmp64 
    fstp        dword ptr -6[bp] 
    fldz        
    fcomp       dword ptr -6[bp] 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp39 
    mov         al,46H 
    jmp         tmp43 
tmp39:
    fld         dword ptr -6[bp] 
    fst         qword ptr -16H[bp] 
    fcomp       qword ptr DGROUP:tmp65 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp40 
    mov         al,41H 
    jmp         tmp43 
tmp40:
    fld         qword ptr -16H[bp] 
    fcomp       qword ptr DGROUP:tmp66 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp41 
    mov         al,42H 
    jmp         tmp43 
tmp41:
    fld         qword ptr -16H[bp] 
    fcomp       qword ptr DGROUP:tmp67 
    fstsw       word ptr -2[bp] 
    nop         
    fwait       
    mov         ax,word ptr -2[bp] 
    sahf        
    jbe         tmp42 
    mov         al,43H 
    jmp         tmp43 
tmp42:
    mov         al,44H 
tmp43:
    mov         sp,bp 
    pop         bp 
    pop         bx 
    ret         
show_secret_:
    push        ax 
    mov         ax,2eH 
    call        near ptr __STK 
    pop         ax 
    push        bx 
    push        cx 
    push        dx 
    push        si 
    push        di 
    push        bp 
    mov         bp,sp 
    sub         sp,20H 
    mov         di,ax 
    mov         si,0ffffH 
    xor         bx,bx 
    mov         ax,offset DGROUP:tmp68 
    call        near ptr r_print_ 
    lea         ax,-20H[bp] 
    call        near ptr readline_unsafe_ 
    mov         dx,offset DGROUP:tmp69 
    lea         ax,-20H[bp] 
    call        near ptr r_streql_ 
    test        ax,ax 
    je          tmp44 
    call        near ptr r_exit_ 
tmp44:
    mov         dx,offset DGROUP:tmp70 
    lea         ax,-20H[bp] 
    call        near ptr r_streql_ 
    test        ax,ax 
    je          tmp45 
    jmp         near ptr tmp16 
tmp45:
    mov         cl,5 
tmp46:
    cmp         bx,3 
    jge         tmp48 
    mov         dx,bx 
    shl         dx,cl 
    add         dx,offset _products 
    lea         ax,-20H[bp] 
    call        near ptr r_streql_ 
    test        ax,ax 
    je          tmp47 
    mov         si,bx 
    jmp         tmp48 
tmp47:
    inc         bx 
    jmp         tmp46 
tmp48:
    cmp         si,0ffffH 
    jne         tmp49 
    mov         ax,offset DGROUP:tmp71 
    jmp         tmp51 
tmp49:
    test        di,di 
    je          tmp50 
    mov         ax,si 
    call        near ptr profit_mark_of_ 
    mov         byte ptr -20H[bp],al 
    mov         byte ptr -1fH[bp],0 
    mov         ax,offset DGROUP:tmp72 
    call        near ptr r_print_ 
    shl         si,1 
    shl         si,1 
    mov         ax,word ptr _input_price[si] 
    mov         dx,word ptr _input_price+2[si] 
    call        near ptr r_print_long_ 
    mov         ax,offset DGROUP:tmp73 
    call        near ptr r_print_ 
    mov         ax,word ptr _output_price[si] 
    mov         dx,word ptr _output_price+2[si] 
    call        near ptr r_print_long_ 
    mov         ax,offset DGROUP:tmp74 
    call        near ptr r_print_ 
    lea         ax,-20H[bp] 
    jmp         tmp51 
tmp50:
    lea         ax,-20H[bp] 
tmp51:
    call        near ptr echo_ 
    jmp         near ptr tmp16 
fake_main_:
    mov         ax,4 
    call        near ptr __STK 
    push        dx 
    xor         dx,dx 
    jmp         tmp53 
tmp52:
    inc         dx 
    cmp         dx,3 
    jge         tmp55 
tmp53:
    call        near ptr login_ 
    test        ax,ax 
    je          tmp52 
tmp54:
    mov         ax,1 
    call        near ptr show_secret_ 
    jmp         tmp54 
tmp55:
    xor         ax,ax 
    call        near ptr show_secret_ 
    jmp         tmp55 
_TEXT		ENDS
CONST		SEGMENT	WORD PUBLIC USE16 'DATA'
tmp56:
    DB	0, 0e4H, 0bH, 54H, 2, 0, 0, 0
tmp57:
    DB	0aH, 0, 0, 0, 0, 0, 0, 0
tmp58:
    DB	0dH, 0aH, 0
tmp59:
    DB	59H, 6fH, 75H, 72H, 20H, 6eH, 61H, 6dH
    DB	65H, 20H, 70H, 6cH, 65H, 61H, 73H, 65H
    DB	3aH, 20H, 0
tmp60:
    DB	50H, 65H, 72H, 6dH, 69H, 73H, 73H, 69H
    DB	6fH, 6eH, 20H, 64H, 65H, 6eH, 69H, 65H
    DB	64H, 2eH, 0
tmp61:
    DB	59H, 6fH, 75H, 72H, 20H, 70H, 61H, 73H
    DB	73H, 77H, 6fH, 72H, 64H, 20H, 70H, 6cH
    DB	65H, 61H, 73H, 65H, 3aH, 20H, 0
tmp62:
    DB	50H, 61H, 73H, 73H, 65H, 64H, 2eH, 0
tmp63:
    DB	49H, 6eH, 66H, 6fH, 72H, 6dH, 61H, 74H
    DB	69H, 6fH, 6eH, 20H, 64H, 65H, 63H, 72H
    DB	79H, 70H, 74H, 65H, 64H, 2eH, 0, 0
tmp64:
    DB	0, 0, 80H, 0bfH, 0, 0, 0, 0
tmp65:
    DB	0cdH, 0ccH, 0ccH, 0ccH, 0ccH, 0ccH, 0ecH, 3fH
tmp66:
    DB	0, 0, 0, 0, 0, 0, 0e0H, 3fH
tmp67:
    DB	9aH, 99H, 99H, 99H, 99H, 99H, 0c9H, 3fH
tmp68:
    DB	57H, 68H, 61H, 74H, 20H, 70H, 72H, 6fH
    DB	64H, 75H, 63H, 74H, 20H, 3fH, 20H, 0
tmp69:
    DB	71H, 0
tmp70:
    DB	0
tmp71:
    DB	4eH, 6fH, 74H, 20H, 66H, 6fH, 75H, 6eH
    DB	64H, 2eH, 0
tmp72:
    DB	49H, 6eH, 70H, 75H, 74H, 20H, 70H, 72H
    DB	69H, 63H, 65H, 20H, 0
tmp73:
    DB	2cH, 20H, 6fH, 75H, 74H, 70H, 75H, 74H
    DB	20H, 70H, 72H, 69H, 63H, 65H, 20H, 0
tmp74:
    DB	2cH, 20H, 70H, 72H, 6fH, 66H, 69H, 74H
    DB	20H, 72H, 61H, 74H, 65H, 20H, 0

CONST		ENDS
CONST2		SEGMENT	WORD PUBLIC USE16 'DATA'
CONST2		ENDS
_DATA		SEGMENT	WORD PUBLIC USE16 'DATA'
_user:
    DB	62H, 65H, 6eH, 73H, 6fH, 6eH, 67H, 20H
    DB	6cH, 69H, 75H, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
_IllIlIlIOoOoOo0o:
    DB	0e2H, 0aH, 0, 0, 0d2H, 15H, 0, 0
    DB	0e6H, 0fH, 0, 0, 0e2H, 0aH, 0, 0
    DB	0efH, 15H, 0, 0, 55H, 4, 0, 0
    DB	0e6H, 0fH, 0, 0, 0e6H, 0fH, 0, 0
    DB	50H, 13H, 0, 0, 5fH, 7, 0, 0
    DB	0beH, 4, 0, 0, 0e0H, 15H, 0, 0
    DB	92H, 0dH, 0, 0, 98H, 0, 0, 0
    DB	45H, 7, 0, 0, 0, 0, 0, 0
    DB	07H DUP(0,0,0,0,0,0,0,0)
    DB	0, 0, 0, 0, 0, 0, 0, 0
_IllIllIl0OoOO00o:
    DB	0dH, 16H, 19H, 1
_llIlIIlIO0O0ooO0:
    DB	0ffH, 0bbH, 1aH, 0faH
_products:
    DB	62H, 6fH, 6fH, 6bH, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	70H, 65H, 6eH, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	73H, 63H, 61H, 6cH, 61H, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
_input_price:
    DB	0f3H, 0bdH, 76H, 1, 0fcH, 0e8H, 35H, 1
    DB	0b3H, 3aH, 35H, 1
_output_price:
    DB	0fH, 0b0H, 7, 1, 0a1H, 0c2H, 35H, 1
    DB	16H, 0b5H, 35H, 1
tmp75:
    DB	0, 0, 0
tmp76:
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0
tmp77:
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0
    DB	0, 0, 0, 0, 0, 0, 0, 0

_DATA		ENDS
		END
