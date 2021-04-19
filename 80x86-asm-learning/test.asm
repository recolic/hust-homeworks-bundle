.387
		PUBLIC	main_
		EXTRN	__STK:BYTE
		EXTRN	func_:BYTE
		EXTRN	printf_:BYTE
		EXTRN	_small_code_:BYTE
		EXTRN	_cstart_:BYTE
DGROUP		GROUP	CONST,CONST2,_DATA
_TEXT		SEGMENT	BYTE PUBLIC USE16 'CODE'
		ASSUME CS:_TEXT, DS:DGROUP, SS:DGROUP
main_:
mul bx
    mov         ax,6 
    call        near ptr __STK 
    mov         ax,1 
    call        near ptr func_ 
    push        ax 
    mov         ax,offset DGROUP:L$1 
    push        ax 
    call        near ptr printf_ 
    add         sp,4 
    xor         ax,ax 
    ret         
_TEXT		ENDS
CONST		SEGMENT	WORD PUBLIC USE16 'DATA'
L$1:
    DB	69H, 20H, 69H, 73H, 20H, 25H, 64H, 0aH
    DB	0

CONST		ENDS
CONST2		SEGMENT	WORD PUBLIC USE16 'DATA'
CONST2		ENDS
_DATA		SEGMENT	WORD PUBLIC USE16 'DATA'
_DATA		ENDS
		END
