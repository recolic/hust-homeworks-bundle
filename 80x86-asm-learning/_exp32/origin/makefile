submit: main impl-asm
	wlink name main.exe file main.obj,impl.obj

exe: main impl
	wlink name main.exe file main.obj,impl.obj

main:
	wcc main.c -i=C:\watcom\h
	wdis -a main.obj > main.asm

main-asm:
	wasm main.asm

impl:
	wcc impl.c -i=C:\watcom\h
	wdis -a impl.obj > impl.asm

impl-asm:
	wasm impl.asm
	
unix:
	gcc impl.c main.c -std=c89
