exe:
	wlink name main.exe file main.obj,entry.obj

entry:
	wcc entry.c

main:
	wcc main.c -i=C:\watcom\h
	wdis -a main.obj > main.asm

asm:
	wasm main.asm

unix:
	gcc main.c entry.c -std=c89 -g -O0
