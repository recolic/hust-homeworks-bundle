.387
		PUBLIC	main_
		EXTRN	__STK:BYTE
		EXTRN	printf_:BYTE
		EXTRN	_small_code_:BYTE
		EXTRN	_cstart_:BYTE
DGROUP		GROUP	CONST,CONST2,_DATA
_TEXT		SEGMENT	BYTE PUBLIC USE16 'CODE'
		ASSUME CS:_TEXT, DS:DGROUP, SS:DGROUP
main_:
    mov         ax,4 
    call        near ptr __STK 
    mov         ax,offset DGROUP:L$1 
    push        ax 
    call        near ptr printf_ 
    add         sp,2 
    mov         ax,offset DGROUP:L$1 
    push        ax 
    call        near ptr printf_ 
    add         sp,2 
    mov         ax,offset DGROUP:L$2 
    push        ax 
    call        near ptr printf_ 
    add         sp,2 
    xor         ax,ax 
    ret         
_TEXT		ENDS
CONST		SEGMENT	WORD PUBLIC USE16 'DATA'
L$1:
    DB	74H, 65H, 73H, 74H, 0dH, 0aH, 0
L$2:
    DB	74H, 65H, 73H, 74H, 0aH, 0

CONST		ENDS
CONST2		SEGMENT	WORD PUBLIC USE16 'DATA'
CONST2		ENDS
_DATA		SEGMENT	WORD PUBLIC USE16 'DATA'
_DATA		ENDS
		END
