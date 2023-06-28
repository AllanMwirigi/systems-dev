# cc -m32 -S sample.c - compile to 32bit assembly code

	.file	"sample.c"
	.text
	.globl	A
	.type	A, @function
A:
.LFB0:
	.cfi_startproc
	# Entry Code
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp # establish stack frame
	# entry code first saves FP(%bp) onto the stack then lets FP point to the saved FP of the caller
	# stack contents become 
	#              SP
	# ---------------------------------------------------
	#  xxx | PC | FP |												Low address
	# ----------------------------------------------------
	#             FP

	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp # shift SP downward 20 bytes to allocate space for local vars and working area
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax

	# Function body code
	movl	$4, -20(%ebp) # d=4
	movl	$5, -16(%ebp) # e=5
	movl	$6, -12(%ebp) # f=6

	# while inside a function FP points at a fixed location and acts as a base reg for accessing
	# local vars and params. The 3 locals d,e,f each 4bytes long are at the byte offsets -20,-16,-12
	# from FP. After assigning values, stack contents become

	#                 SP ----20 bytes----> SP
	# ------------------- -4  -8 -12 -16 -20 -------------
	#  xxx | retPC | FP | ? | ? | 6 | 5 | 4 | 
	# ----------------------------------------------------
	#             FP

  # call B(d,e) : push params d,e in reverse order
	subl	$8, %esp 	# create 8 bytes TEMP slots on stack
	pushl	-16(%ebp)	# push e
	pushl	-20(%ebp) # push d

	# 																											SP
	# ------------------- -4  -8 -12 -16 -20 | TEMP  |-------------------
	#  xxx | retPC | FP | ? | ? | 6 | 5 | 4 | ? | ? | e | d |
	# -------------------------------------------------------------------
	#             FP

	movl	%eax, %ebx
	call	B@PLT			# grows stack to the right
	# B returns
	addl	$16, %esp 			# clean stack
	movl	%eax, -12(%ebp)	# f = return value in AX
	nop
	movl	-4(%ebp), %ebx

	# Exit code
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret # pop retPC from the stack top into PC
	.cfi_endproc
.LFE0:
	.size	A, .-A
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB1:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE1:
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
