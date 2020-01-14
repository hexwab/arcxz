reloc: /* in: inaddr, size, outaddr */
	mov r3,r2
loop:	ldmia r0!, {r4-r11}
	stmia r2!, {r4-r11}
	subs r1,r1,#32
	bpl loop
	mov pc, r3
