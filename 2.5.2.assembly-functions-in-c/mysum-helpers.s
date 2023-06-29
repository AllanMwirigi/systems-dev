.text
.global mysum # export mysum

mysum:
  # see 2.4.5 for 64bit equivalents pushq, popq, movq
  pushl %ebp
  movl %esp, %ebp

  # caller has pushed y,x onto stack
  #        12   8   4    0
	# -------------------------------------
	#      | y | x | PC | FP |				Low address
	# -------------------------------------
	#                    ebp
  #                    esp

  movl 8(%ebp), %eax  # AX = x
  addl 12(%ebp), %eax # AX += y

  # deallocate stack space
  movl %ebp, %esp
  pop %ebp

  ret # pop retPC from the stack top into PC thus returning to caller
