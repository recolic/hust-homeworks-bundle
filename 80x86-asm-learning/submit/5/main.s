	.file	"main.rasm"
	.intel_syntax noprefix
	.globl	_hShowWin
	.bss
	.align 4
_hShowWin:
	.space 4
	.section .rdata,"dr"
LC0:
	.ascii "Hi\0"
	.align 4
LC1:
	.ascii "By Bensong Liu <root@recolic.net>, Licensed under Modified Mozilla Public License 2.0.\0"
	.text
	.globl	_mainWinProc@16
	.def	_mainWinProc@16;	.scl	2;	.type	32;	.endef
_mainWinProc@16:
LFB11:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 120
	mov	eax, DWORD PTR [ebp+12]
	cmp	eax, 5
	je	L3
	cmp	eax, 5
	ja	L4
	cmp	eax, 1
	je	L5
	cmp	eax, 2
	je	L6
	jmp	L2
L4:
	cmp	eax, 15
	je	L7
	cmp	eax, 273
	je	L8
	jmp	L2
L5:
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_DrawMenuBar@4
	sub	esp, 4
	jmp	L9
L7:
	lea	eax, [ebp-76]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_BeginPaint@8
	sub	esp, 8
	mov	DWORD PTR [ebp-12], eax
	mov	DWORD PTR [esp+8], 6
	lea	eax, [ebp-76]
	add	eax, 8
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp], eax
	call	_FillRect@12
	sub	esp, 12
	lea	eax, [ebp-76]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_EndPaint@8
	sub	esp, 8
	nop
	jmp	L9
L3:
	mov	eax, DWORD PTR [ebp+20]
	shr	eax, 16
	movzx	eax, ax
	lea	ecx, [eax-20]
	mov	eax, DWORD PTR [ebp+20]
	movzx	eax, ax
	lea	edx, [eax-20]
	mov	eax, DWORD PTR _hShowWin
	mov	DWORD PTR [esp+24], 0
	mov	DWORD PTR [esp+20], ecx
	mov	DWORD PTR [esp+16], edx
	mov	DWORD PTR [esp+12], 10
	mov	DWORD PTR [esp+8], 10
	mov	DWORD PTR [esp+4], 0
	mov	DWORD PTR [esp], eax
	call	_SetWindowPos@28
	sub	esp, 28
	jmp	L9
L8:
	mov	eax, DWORD PTR [ebp+16]
	movzx	eax, ax
	cmp	eax, 2
	je	L11
	cmp	eax, 2
	jg	L12
	cmp	eax, 1
	je	L13
	jmp	L9
L12:
	cmp	eax, 3
	je	L14
	cmp	eax, 4
	je	L15
	jmp	L9
L13:
	mov	DWORD PTR [esp+12], 0
	mov	DWORD PTR [esp+8], 0
	mov	DWORD PTR [esp+4], 16
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_PostMessageA@16
	sub	esp, 16
	jmp	L10
L11:
	call	_calc_average
	jmp	L10
L14:
	call	_show_list
	jmp	L10
L15:
	mov	DWORD PTR [esp+12], 0
	mov	DWORD PTR [esp+8], OFFSET FLAT:LC0
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC1
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_MessageBoxA@16
	sub	esp, 16
	nop
L10:
	jmp	L9
L6:
	mov	DWORD PTR [esp], 0
	call	_PostQuitMessage@4
	sub	esp, 4
	jmp	L9
L2:
	mov	eax, DWORD PTR [ebp+20]
	mov	DWORD PTR [esp+12], eax
	mov	eax, DWORD PTR [ebp+16]
	mov	DWORD PTR [esp+8], eax
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_DefWindowProcA@16
	sub	esp, 16
	jmp	L16
L9:
	mov	eax, 0
L16:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	16
	.cfi_endproc
LFE11:
	.section .rdata,"dr"
LC2:
	.ascii "File\0"
LC3:
	.ascii "Action\0"
LC4:
	.ascii "Help\0"
LC5:
	.ascii "Exit\0"
LC6:
	.ascii "Average\0"
LC7:
	.ascii "List\0"
LC8:
	.ascii "About\0"
LC9:
	.ascii "Recolic's Homework\0"
LC10:
	.ascii "Ready.\0"
LC11:
	.ascii "EDIT\0"
	.text
	.globl	_WinMain@16
	.def	_WinMain@16;	.scl	2;	.type	32;	.endef
_WinMain@16:
LFB12:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	edi
	sub	esp, 164
	.cfi_offset 7, -12
	mov	DWORD PTR [ebp-43], 1852405618
	mov	DWORD PTR [ebp-39], 1634493229
	mov	DWORD PTR [ebp-35], 761492339
	mov	WORD PTR [ebp-31], 12592
	mov	BYTE PTR [ebp-29], 0
	lea	edx, [ebp-84]
	mov	eax, 0
	mov	ecx, 10
	mov	edi, edx
	rep stosd
	mov	DWORD PTR [ebp-80], OFFSET FLAT:_mainWinProc@16
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [ebp-68], eax
	lea	eax, [ebp-43]
	mov	DWORD PTR [ebp-48], eax
	lea	eax, [ebp-84]
	mov	DWORD PTR [esp], eax
	call	_RegisterClassA@4
	sub	esp, 4
	call	_CreateMenu@0
	mov	DWORD PTR [ebp-12], eax
	call	_CreatePopupMenu@0
	mov	DWORD PTR [ebp-16], eax
	call	_CreatePopupMenu@0
	mov	DWORD PTR [ebp-20], eax
	call	_CreatePopupMenu@0
	mov	DWORD PTR [ebp-24], eax
	mov	eax, DWORD PTR [ebp-16]
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC2
	mov	DWORD PTR [esp+8], eax
	mov	DWORD PTR [esp+4], 16
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	eax, DWORD PTR [ebp-20]
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC3
	mov	DWORD PTR [esp+8], eax
	mov	DWORD PTR [esp+4], 16
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	eax, DWORD PTR [ebp-24]
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC4
	mov	DWORD PTR [esp+8], eax
	mov	DWORD PTR [esp+4], 16
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC5
	mov	DWORD PTR [esp+8], 1
	mov	DWORD PTR [esp+4], 0
	mov	eax, DWORD PTR [ebp-16]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC6
	mov	DWORD PTR [esp+8], 2
	mov	DWORD PTR [esp+4], 0
	mov	eax, DWORD PTR [ebp-20]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC7
	mov	DWORD PTR [esp+8], 3
	mov	DWORD PTR [esp+4], 0
	mov	eax, DWORD PTR [ebp-20]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	DWORD PTR [esp+12], OFFSET FLAT:LC8
	mov	DWORD PTR [esp+8], 4
	mov	DWORD PTR [esp+4], 0
	mov	eax, DWORD PTR [ebp-24]
	mov	DWORD PTR [esp], eax
	call	_AppendMenuA@16
	sub	esp, 16
	mov	DWORD PTR [esp+44], 0
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp+40], eax
	mov	eax, DWORD PTR [ebp-12]
	mov	DWORD PTR [esp+36], eax
	mov	DWORD PTR [esp+32], 0
	mov	DWORD PTR [esp+28], -2147483648
	mov	DWORD PTR [esp+24], -2147483648
	mov	DWORD PTR [esp+20], -2147483648
	mov	DWORD PTR [esp+16], -2147483648
	mov	DWORD PTR [esp+12], 13565952
	mov	DWORD PTR [esp+8], OFFSET FLAT:LC9
	lea	eax, [ebp-43]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], 0
	call	_CreateWindowExA@48
	sub	esp, 48
	mov	DWORD PTR [ebp-28], eax
	mov	DWORD PTR [esp+44], 0
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp+40], eax
	mov	DWORD PTR [esp+36], 0
	mov	eax, DWORD PTR [ebp-28]
	mov	DWORD PTR [esp+32], eax
	mov	DWORD PTR [esp+28], 1000
	mov	DWORD PTR [esp+24], 1000
	mov	DWORD PTR [esp+20], 10
	mov	DWORD PTR [esp+16], 10
	mov	DWORD PTR [esp+12], 1342177476
	mov	DWORD PTR [esp+8], OFFSET FLAT:LC10
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC11
	mov	DWORD PTR [esp], 0
	call	_CreateWindowExA@48
	sub	esp, 48
	mov	DWORD PTR _hShowWin, eax
	mov	eax, DWORD PTR [ebp-28]
	mov	DWORD PTR [esp], eax
	call	_DrawMenuBar@4
	sub	esp, 4
	mov	DWORD PTR [esp+4], 5
	mov	eax, DWORD PTR [ebp-28]
	mov	DWORD PTR [esp], eax
	call	_ShowWindow@8
	sub	esp, 8
	mov	eax, DWORD PTR _hShowWin
	mov	DWORD PTR [esp+4], 5
	mov	DWORD PTR [esp], eax
	call	_ShowWindow@8
	sub	esp, 8
	mov	eax, DWORD PTR [ebp-28]
	mov	DWORD PTR [esp], eax
	call	_UpdateWindow@4
	sub	esp, 4
	mov	eax, DWORD PTR _hShowWin
	mov	DWORD PTR [esp], eax
	call	_UpdateWindow@4
	sub	esp, 4
	jmp	L18
L19:
	lea	eax, [ebp-112]
	mov	DWORD PTR [esp], eax
	call	_TranslateMessage@4
	sub	esp, 4
	lea	eax, [ebp-112]
	mov	DWORD PTR [esp], eax
	call	_DispatchMessageA@4
	sub	esp, 4
L18:
	mov	DWORD PTR [esp+12], 0
	mov	DWORD PTR [esp+8], 0
	mov	DWORD PTR [esp+4], 0
	lea	eax, [ebp-112]
	mov	DWORD PTR [esp], eax
	call	_GetMessageA@16
	sub	esp, 16
	test	eax, eax
	jne	L19
	mov	eax, 0
	mov	edi, DWORD PTR [ebp-4]
	leave
	.cfi_restore 5
	.cfi_restore 7
	.cfi_def_cfa 4, 4
	ret	16
	.cfi_endproc
LFE12:
	.ident	"RecolicLangC bata-1.0.1.6"
	.def	_DrawMenuBar@4;	.scl	2;	.type	32;	.endef
	.def	_BeginPaint@8;	.scl	2;	.type	32;	.endef
	.def	_FillRect@12;	.scl	2;	.type	32;	.endef
	.def	_EndPaint@8;	.scl	2;	.type	32;	.endef
	.def	_SetWindowPos@28;	.scl	2;	.type	32;	.endef
	.def	_PostMessageA@16;	.scl	2;	.type	32;	.endef
	.def	_calc_average;	.scl	2;	.type	32;	.endef
	.def	_show_list;	.scl	2;	.type	32;	.endef
	.def	_MessageBoxA@16;	.scl	2;	.type	32;	.endef
	.def	_PostQuitMessage@4;	.scl	2;	.type	32;	.endef
	.def	_DefWindowProcA@16;	.scl	2;	.type	32;	.endef
	.def	_RegisterClassA@4;	.scl	2;	.type	32;	.endef
	.def	_CreateMenu@0;	.scl	2;	.type	32;	.endef
	.def	_CreatePopupMenu@0;	.scl	2;	.type	32;	.endef
	.def	_AppendMenuA@16;	.scl	2;	.type	32;	.endef
	.def	_CreateWindowExA@48;	.scl	2;	.type	32;	.endef
	.def	_ShowWindow@8;	.scl	2;	.type	32;	.endef
	.def	_UpdateWindow@4;	.scl	2;	.type	32;	.endef
	.def	_TranslateMessage@4;	.scl	2;	.type	32;	.endef
	.def	_DispatchMessageA@4;	.scl	2;	.type	32;	.endef
	.def	_GetMessageA@16;	.scl	2;	.type	32;	.endef
