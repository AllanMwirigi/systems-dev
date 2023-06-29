.text
.global sub, a, b, printf # import

sub:
  pushl %ebp
  movl %esp, %ebp

  pushl b
  pushl a
  pushl $fmt  # push value (address) of fmt
  call printf # printf(fmt, a, b)
  addl $12, %esp

  movl %ebp, %esp
  popl %ebp
  ret

.data
fmt: .asciz "a=%d b=%d\n"


