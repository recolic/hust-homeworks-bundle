fake: main impl-asm
	wlink name main.exe file main.obj,impl.obj

main:
	wcc main.c -i=C:\watcom\h

impl-asm:
	wasm impl.asm

clean:
	del main.obj main.exe impl.obj main.err

report:
	echo ';;;;;;;;;;;;main.c' && cat main.c && echo ';;;;;;;;;;;;;;;afx.h' && cat afx.h && echo ';;;;;;;;;;;;;impl.asm' && cat impl.asm && echo ';;;;;;;;;;;;;;;;makefile' && cat makefile
