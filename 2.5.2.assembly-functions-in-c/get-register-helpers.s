# these functions are simple and don't need to establish and allocate stack frames
# Need to make functions global in order to be accessed in another file with extern
.global get_esp, get_ebp

get_esp:
  movl %esp, %eax
  ret

get_ebp:
  movl %ebp, %eax
  ret
