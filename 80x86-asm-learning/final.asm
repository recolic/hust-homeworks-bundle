.386

STACK SEGMENT USE16 STACK
        DB 200 DUP(0)
STACK ENDS

DATA SEGMENT USE16
bname db 'bensongliu',0
bpass db 'test',0,0
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
in_name   DB 12
		  DB ?
		  DB 12 DUP (0)
in_pwd    DB 8
		  DB ?
		  DB 8 DUP(0)
in_product DB 12
		   DB ?
		   DB 12 DUP(0)
PR1 DW 0
PR2 DW 0
APR DW 0
CRLF DB 0AH,0DH,'$'
AUTH DB 0H
BUF1 DB 'User: $'
BUF2 DB 'Password: $'
BUF3 DB 'There is an error!$'
BUF4 DB 'Wrong password.$'
BUF5 DB 'The name of product ? $'
DATA ENDS

CODE SEGMENT USE16
        ASSUME CS:CODE, DS:DATA, SS:STACK
START:
	;input the name and password
	MOV AX,DATA
	MOV DS,AX
	LEA DX,BUF1
	MOV AH,9
		INT 21H
	LEA DX,OFFSET in_name
	MOV AH,10
		INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	
	;JUDGE IF IT IS LEGAL
	CMP in_name[1],0
	JE L4
	MOV BH,in_name+2
	CMP BH,'q'
	JE L2
	LEA DX,BUF2
	MOV AH,9
		INT 21H
	LEA DX,OFFSET in_pwd
	MOV AH,10
		INT 21H
		
	;JUDGE IF THE NAME RIGHT
	JMP L5
	;JUDGE IF THE PASSWORD RIGHT
	JMP L6
	
	MOV AX, 4C00H
        INT 21H	
	

	
		
L1:MOV AX, 4C00H      ;End
        INT 21H	
	
	
L2: MOV BH,in_name+1   ;judge if it is 'q'
	CMP BH,1
	JE L1

L3:	MOV AX, 4C00H;QUIT
        INT 21H

L4: 
	MOV AUTH,0
	JMP L8
		

;JUDGE WHETHER THE NAME IS RIGHT	
L5: 
	MOV DI,OFFSET in_name
	MOV BX,DI
	INC BX
	MOV SI,10
	MOV BX,[BX]
	MOV BH,0;因为16位，需要删除高8位
	CMP SI,BX
	JNE L7

	
NEXT1:
	MOV CH,1[DI][BX]
	MOV CL,[BNAME+BX-1]
	CMP CH,CL
	JNE L7
	DEC SI
	JNE NEXT1
	JMP L6
	
;JUDGE WHETHER THE PASSWORD IS RIGHT
L6:	MOV DI,OFFSET in_pwd
	MOV BX,DI
	INC BX
	MOV SI,4
	MOV BX,[BX]
	MOV BH,0 ;因为16位，需要删除高8位
	CMP SI,BX
	JNE L7

NEXT2:
	MOV CH,1[DI][BX]
	MOV CL,[BPASS+BX-1]
	CMP CH,CL
	JNE L7
	DEC SI
	JNE NEXT2
	MOV AUTH,1H
	JMP L8
		
L7: LEA DX,CRLF
	MOV AH,9
	INT 21H
	LEA DX,BUF4
	MOV AH,9
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	JMP START
		
;功能三judge if the input is legal
L8: LEA DX,CRLF
	MOV AH,9
	INT 21H
	LEA DX,BUF5
	MOV AH,9
	INT 21H
	LEA DX,OFFSET in_product
	MOV AH,10
		INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	CMP in_product[1],0
	JE START
	JMP L9

;search the product
L9: 
	MOV DI,OFFSET S1
	ADD DI,6          ;第一个商店第一个商品的地址
	MOV BL,[in_product+1]         ;偏移地址
	MOV BH,0
	MOV SI,OFFSET in_product
	CMP BX,10
	JE NEXT3
	MOV DX,[DI+BX]  ;防止输入商品名为内置商品名的子集时也搜索成功
	CMP DX,0
	JNE L11
NEXT3:
	
	MOV CH,[SI+BX+1]
	MOV CL,[DI+BX-1]
	CMP CL,0
	JE L11
	CMP CH,CL
	JNE L11
	JMP L10
	
;if the char is same
L10:CMP BX,1
	JE L12          ;FIND THE PRODUCT
	DEC BX
	JMP NEXT3

;if the char is different
L11:
	ADD DI,20
	MOV BL,[in_product+1]
	MOV BH,0
	MOV CX,OFFSET S1
	CMP CX,DI
	JE L8      ;Fail to search,repeat to input
	JMP NEXT3
	
L12	:
	CMP AUTH,1
	JE L13
	MOV BL,[in_product+1]
	MOV BH,0
	MOV CH,'$'
	MOV 2[SI][BX],CH
	LEA DX,in_product+2
	MOV AH,9
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	JMP START
	
L13:ADD DI,10
	MOV AX,[DI+2]
	MOV BX,[DI+6]
	IMUL AX,BX
	MOV BX,[DI]
	MOV CX,[DI+4]
	IMUL BX,CX
	MOV CX,BX
	SUB AX,BX
	CWD
	MOV BX,100
	IMUL AX,BX
	MOV BX,CX
	IDIV BX
	MOV BX,OFFSET PR1
	MOV [BX],AX
	JMP L14
	
L14:
;search the product
L15: 
	MOV DI,OFFSET S2
	ADD DI,6          ;第二个商店第一个商品的地址
	MOV BL,[in_product+1]         ;偏移地址
	MOV BH,0
	MOV SI,OFFSET in_product
	CMP BX,10
	JE NEXT4
	MOV DX,[DI+BX]  ;防止输入商品名为内置商品名的子集时也搜索成功
	CMP DX,0
	JNE L17
NEXT4:
	
	MOV CH,[SI+BX+1]
	MOV CL,[DI+BX-1]
	CMP CL,0
	JE L17
	CMP CH,CL
	JNE L17
	JMP L16
	
;if the char is same
L16:CMP BX,1
	JE L19         ;FIND THE PRODUCT
	DEC BX
	JMP NEXT4

;if the char is different
L17:
	ADD DI,20
	MOV BL,[in_product+1]
	MOV BH,0
	MOV CX,OFFSET in_name
	CMP CX,DI
	JE L8      ;Fail to search,repeat to input
	JMP NEXT4
	
L19:ADD DI,10
	MOV AX,[DI+2]
	MOV BX,[DI+6]
	IMUL AX,BX
	MOV BX,[DI]
	MOV CX,[DI+4]
	IMUL BX,CX
	MOV CX,BX
	SUB AX,BX
	CWD
	MOV BX,100
	IMUL AX,BX
	MOV BX,CX
	IDIV BX
	
	MOV BX,OFFSET PR2
	MOV [BX],AX
	MOV DI,OFFSET PR1
	MOV AX,[DI]
	CWD
	ADD AX,[BX]
	MOV BX,2
	IDIV BX
	MOV BX,OFFSET APR
	MOV [BX],AX
	JMP L20
	
	
L20:MOV CX,'A'
	CMP AX,90
	JGE L21
	INC CX
	CMP AX,50
	JGE L21
	INC CX
	CMP AX,20
	JGE L21
	INC CX
	CMP AX,0
	JGE L21
	INC CX
	JMP L21
	
	
	
	
L21:
	MOV DL,CL
	MOV AH,2
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	JMP START
	
	















		
CODE ENDS
END START
END L4
