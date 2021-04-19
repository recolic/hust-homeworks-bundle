	.file	"impl.rlang"
	.intel_syntax noprefix
	.globl	_calc_done
	.bss
	.align 4
_calc_done:
	.space 4
	.globl	_products
	.data
	.align 32
_products:
	.ascii "scala\0"
	.space 26
	.long	30
	.long	70
	.byte	63
	.space 3
	.ascii "java\0"
	.space 27
	.long	500
	.long	500
	.byte	63
	.space 3
	.ascii "golang\0"
	.space 25
	.long	60
	.long	50
	.byte	63
	.space 3
	.ascii "C++1z\0"
	.space 26
	.long	1000
	.long	1100
	.byte	63
	.space 3
	.ascii "Python\0"
	.space 25
	.long	10
	.long	1000
	.byte	63
	.space 3
	.ascii "Assembly\0"
	.space 23
	.long	100000
	.long	1
	.byte	63
	.space 3
	.text
	.globl	_profit_mark_of
	.def	_profit_mark_of;	.scl	2;	.type	32;	.endef
_profit_mark_of:
LFB11:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 16
	fld	DWORD PTR [ebp+8]
	fdiv	DWORD PTR [ebp+12]
	fld1
	fsubp	st(1), st
	fstp	DWORD PTR [ebp-4]
	fldz
	fld	DWORD PTR [ebp-4]
	fxch	st(1)
	fucompp
	fnstsw	ax
	sahf
	jbe	L15
	mov	eax, 70
	jmp	L4
L15:
	fld	DWORD PTR [ebp-4]
	fld	QWORD PTR LC2
	fxch	st(1)
	fucompp
	fnstsw	ax
	sahf
	jbe	L16
	mov	eax, 65
	jmp	L4
L16:
	fld	DWORD PTR [ebp-4]
	fld	DWORD PTR LC3
	fxch	st(1)
	fucompp
	fnstsw	ax
	sahf
	jbe	L17
	mov	eax, 66
	jmp	L4
L17:
	fld	DWORD PTR [ebp-4]
	fld	QWORD PTR LC4
	fxch	st(1)
	fucompp
	fnstsw	ax
	sahf
	jbe	L18
	mov	eax, 67
	jmp	L4
L18:
	mov	eax, 68
L4:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.section .rdata,"dr"
LC6:
	.ascii "Calculation done.\0"
	.text
	.globl	_calc_average
	.def	_calc_average;	.scl	2;	.type	32;	.endef
_calc_average:
LFB12:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 56
	mov	eax, DWORD PTR _hShowWin
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC6
	mov	DWORD PTR [esp], eax
	call	_SetWindowTextA@8
	sub	esp, 8
	mov	DWORD PTR _calc_done, 1
	mov	DWORD PTR [ebp-12], 0
	jmp	L20
L21:
	mov	eax, DWORD PTR [ebp-12]
	imul	eax, eax, 44
	add	eax, OFFSET FLAT:_products+32
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [ebp-28], eax
	fild	DWORD PTR [ebp-28]
	mov	eax, DWORD PTR [ebp-12]
	imul	eax, eax, 44
	add	eax, OFFSET FLAT:_products+36
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [ebp-28], eax
	fild	DWORD PTR [ebp-28]
	fxch	st(1)
	fstp	DWORD PTR [esp+4]
	fstp	DWORD PTR [esp]
	call	_profit_mark_of
	mov	edx, eax
	mov	eax, DWORD PTR [ebp-12]
	imul	eax, eax, 44
	add	eax, OFFSET FLAT:_products+40
	mov	BYTE PTR [eax], dl
	add	DWORD PTR [ebp-12], 1
L20:
	cmp	DWORD PTR [ebp-12], 5
	jle	L21
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_r_memcpy
	.def	_r_memcpy;	.scl	2;	.type	32;	.endef
_r_memcpy:
LFB13:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 16
	mov	DWORD PTR [ebp-4], 0
	jmp	L23
L24:
	mov	edx, DWORD PTR [ebp-4]
	mov	eax, DWORD PTR [ebp+8]
	add	edx, eax
	mov	ecx, DWORD PTR [ebp-4]
	mov	eax, DWORD PTR [ebp+12]
	add	eax, ecx
	movzx	eax, BYTE PTR [eax]
	mov	BYTE PTR [edx], al
	add	DWORD PTR [ebp-4], 1
L23:
	mov	eax, DWORD PTR [ebp-4]
	cmp	eax, DWORD PTR [ebp+16]
	jl	L24
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.globl	_r_strncpy_fillspace
	.def	_r_strncpy_fillspace;	.scl	2;	.type	32;	.endef
_r_strncpy_fillspace:
LFB14:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 16
	mov	DWORD PTR [ebp-4], 0
	mov	DWORD PTR [ebp-8], 0
	jmp	L26
L30:
	cmp	DWORD PTR [ebp-4], 0
	je	L27
	mov	edx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+8]
	add	eax, edx
	mov	BYTE PTR [eax], 32
	jmp	L28
L27:
	mov	edx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+12]
	add	eax, edx
	movzx	eax, BYTE PTR [eax]
	test	al, al
	jne	L29
	mov	DWORD PTR [ebp-4], 1
	mov	edx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+8]
	add	eax, edx
	mov	BYTE PTR [eax], 32
	jmp	L28
L29:
	mov	edx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+8]
	add	edx, eax
	mov	ecx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+12]
	add	eax, ecx
	movzx	eax, BYTE PTR [eax]
	mov	BYTE PTR [edx], al
L28:
	add	DWORD PTR [ebp-8], 1
L26:
	mov	eax, DWORD PTR [ebp-8]
	cmp	eax, DWORD PTR [ebp+16]
	jl	L30
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.globl	_r_long8_to_mem
	.def	_r_long8_to_mem;	.scl	2;	.type	32;	.endef
_r_long8_to_mem:
LFB15:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	sub	esp, 16
	.cfi_offset 3, -12
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 1801439851
	mov	eax, ecx
	imul	edx
	sar	edx, 22
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	edx, eax
	mov	eax, DWORD PTR [ebp+8]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+1]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 1125899907
	mov	eax, ecx
	imul	edx
	sar	edx, 18
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+2]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 351843721
	mov	eax, ecx
	imul	edx
	sar	edx, 13
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+3]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 1759218605
	mov	eax, ecx
	imul	edx
	sar	edx, 12
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+4]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 274877907
	mov	eax, ecx
	imul	edx
	sar	edx, 6
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+5]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 1374389535
	mov	eax, ecx
	imul	edx
	sar	edx, 5
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+6]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	mov	ecx, edx
	sub	ecx, eax
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	eax, DWORD PTR [ebp+8]
	lea	ebx, [eax+7]
	mov	ecx, DWORD PTR [ebp+12]
	mov	edx, 1717986919
	mov	eax, ecx
	imul	edx
	sar	edx, 2
	mov	eax, ecx
	sar	eax, 31
	sub	edx, eax
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	sub	ecx, eax
	mov	edx, ecx
	mov	eax, edx
	add	eax, 48
	mov	BYTE PTR [ebx], al
	mov	DWORD PTR [ebp-8], 0
	jmp	L32
L36:
	mov	edx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+8]
	add	eax, edx
	movzx	eax, BYTE PTR [eax]
	cmp	al, 48
	jne	L37
	mov	edx, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [ebp+8]
	add	eax, edx
	mov	BYTE PTR [eax], 32
	add	DWORD PTR [ebp-8], 1
L32:
	cmp	DWORD PTR [ebp-8], 7
	jle	L36
	jmp	L35
L37:
	nop
L35:
	nop
	add	esp, 16
	pop	ebx
	.cfi_restore 3
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_r_serialize_record
	.def	_r_serialize_record;	.scl	2;	.type	32;	.endef
_r_serialize_record:
LFB16:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 12
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [esp+8], 8
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_r_strncpy_fillspace
	mov	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax+32]
	mov	edx, DWORD PTR [ebp+8]
	add	edx, 8
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], edx
	call	_r_long8_to_mem
	mov	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax+36]
	mov	edx, DWORD PTR [ebp+8]
	add	edx, 16
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], edx
	call	_r_long8_to_mem
	mov	eax, DWORD PTR [ebp+8]
	add	eax, 24
	mov	BYTE PTR [eax], 32
	mov	eax, DWORD PTR [ebp+8]
	lea	edx, [eax+25]
	mov	eax, DWORD PTR [ebp+12]
	movzx	eax, BYTE PTR [eax+40]
	mov	BYTE PTR [edx], al
	mov	eax, DWORD PTR [ebp+8]
	add	eax, 26
	mov	BYTE PTR [eax], 13
	mov	eax, DWORD PTR [ebp+8]
	add	eax, 27
	mov	BYTE PTR [eax], 10
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.globl	_show_list
	.def	_show_list;	.scl	2;	.type	32;	.endef
_show_list:
LFB17:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	edi
	push	ebx
	sub	esp, 240
	.cfi_offset 7, -12
	.cfi_offset 3, -16
	mov	DWORD PTR [ebp-219], 1701667182
	mov	DWORD PTR [ebp-215], 538976288
	mov	DWORD PTR [ebp-211], 1885302377
	mov	DWORD PTR [ebp-207], 1701013874
	mov	DWORD PTR [ebp-203], 1953853216
	mov	DWORD PTR [ebp-199], 1769107551
	mov	DWORD PTR [ebp-195], 1730176355
	mov	DWORD PTR [ebp-191], 1701077362
	mov	DWORD PTR [ebp-187], 2573
	lea	eax, [ebp-183]
	mov	ecx, 167
	mov	ebx, 0
	mov	DWORD PTR [eax], ebx
	mov	DWORD PTR [eax-4+ecx], ebx
	lea	edx, [eax+4]
	and	edx, -4
	sub	eax, edx
	add	ecx, eax
	and	ecx, -4
	shr	ecx, 2
	mov	edi, edx
	mov	eax, ebx
	rep stosd
	mov	DWORD PTR [ebp-12], 34
	mov	DWORD PTR [ebp-16], 0
	jmp	L40
L41:
	mov	eax, DWORD PTR [ebp-16]
	imul	eax, eax, 44
	lea	edx, _products[eax]
	mov	eax, DWORD PTR [ebp-12]
	lea	ecx, [ebp-219]
	add	eax, ecx
	mov	DWORD PTR [esp+4], edx
	mov	DWORD PTR [esp], eax
	call	_r_serialize_record
	add	DWORD PTR [ebp-16], 1
	add	DWORD PTR [ebp-12], 28
L40:
	cmp	DWORD PTR [ebp-16], 5
	jle	L41
	mov	BYTE PTR [ebp-16], 0
	mov	eax, DWORD PTR _hShowWin
	lea	edx, [ebp-219]
	mov	DWORD PTR [esp+4], edx
	mov	DWORD PTR [esp], eax
	call	_SetWindowTextA@8
	sub	esp, 8
	nop
	lea	esp, [ebp-8]
	pop	ebx
	.cfi_restore 3
	pop	edi
	.cfi_restore 7
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.section .rdata,"dr"
	.align 8
LC2:
	.long	-858993459
	.long	1072483532
	.align 4
LC3:
	.long	1056964608
	.align 8
LC4:
	.long	-1717986918
	.long	1070176665
	.ident	"RecolicLangC bata-1.0.1.6"
	.def	_SetWindowTextA@8;	.scl	2;	.type	32;	.endef
