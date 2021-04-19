bname db 'pan xu fei',0
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
in_name   db 12
		  db ?
		  db 12 dup (0)
in_pwd    db 8
		  db ?
		  db 8 dup(0)
in_product db 12
		   db ?
		   db 12 dup(0)
pr1 dw 0
pr2 dw 0
apr dw 0
crlf db 0ah,0dh,'$'
auth db 0h
buf1 db 'please enter your name: $'
buf2 db 'please enter your password: $'
buf3 db 'there is an error!$'
buf4 db 'the name or password input is wrong!please try again!$'
buf5 db 'please enter the name of product:$'

