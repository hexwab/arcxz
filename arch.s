.section .text.startup
.global _start	
_start:
	ldr r13,[pc,#0]
	b main
	.word	stack
.section .text
.global open
open:
	mov r1,r0
	mov r2,#0
	mov r0,#0x4f
	swi 0x0d /*"OS_Find" */
	mov pc,r14
.global close
close:
	mov r1,r0
	mov r0,#0
	swi 0x0d /*"OS_Find" */
	mov pc,r14
.global read	
read:	
	push {r4-r5,r14}
	mov r3,r0
	mov r5,r0
	mov r0,#4
	swi 0x0c /*"OS_GBPB" */
	sub r0,r5,r3
	pop {r4-r5,pc}
.global wrch
wrch:	
	swi 0x46 /*"OS_WriteN" */
	mov pc,r14
.global hex
hex:
	sub r1,r13, #12
	mov r2,#12
	swi 0xd4 /*"OS_ConvertHex8"*/
.global puts
puts:	
	swi 0x02 /*"OS_Write0" */
	mov pc,r14
.global osexit
osexit:	
	swi 0x11 /*"OS_Exit" */
	
