.386
.model small; .code code ;;;;;;;use16
code segment use16
real_int_addr dw ?,?
fake_int_0x16:
cmp ah, 00h
je next
cmp ah, 10h
je next
jmp dword ptr real_int_addr
next:
push bp
mov bp, sp
pushf
call dword ptr real_int_addr
cmp al, 97
jb quit
cmp al, 122
ja quit
sub al, 32
quit:
pop bp
iret
start:
xor ax, ax
mov ds, ax
mov ax, ds:[16h * 4]
mov real_int_addr, ax
mov ax, ds:[16h * 4 + 2]
mov real_int_addr + 2, ax
cli
mov word ptr ds:[16h * 4], offset fake_int_0x16
mov ds:[16h * 4 + 2], cs
sti
mov dx, offset start + 15
shr dx, 4
add dx, 10h
mov ax, 3100h
int 21h
end start
code ends
.386
code segment use16
start: xor ax, axmov ds, ax
mov ax, ds:[16h * 4]
mov cx, ds:[16h * 4 + 2]
mov es, cx
sub ax, 4
cli
mov si, ax
mov bx, es:[si]
mov word ptr ds:[16h * 4], bx
add si, 2
mov ax, es:[si]
mov ds:[16h * 4 + 2], ax
sti
int 49h
mov ax, 4c00h
int 21h
code ends
end start
