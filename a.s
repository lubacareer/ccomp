.data
.text
.globl main
main:
  pushq %rbp
  movq %rsp, %rbp
  subq $128, %rsp
  movl $5, %eax
  movl %eax, -20(%rbp)
  movl $3, %eax
  movl %eax, -24(%rbp)
  movl %eax, -12(%rbp)
  movl %eax, -16(%rbp)
  movl %eax, -24(%rbp)
  movl %eax, -28(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  addl %ecx, %eax
  movl %eax, -40(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  subl %ecx, %eax
  movl %eax, -44(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -48(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -52(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -56(%rbp)
  movl %eax, -60(%rbp)
  movl %eax, -64(%rbp)
  movl %eax, -68(%rbp)
  movl %eax, -72(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -76(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -80(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -84(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -88(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -92(%rbp)
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  movl %eax, -96(%rbp)
  movl $10, %eax
  pushq %rax
  movl -24(%rbp), %eax
  popq %rcx
  pushq %rax
  movl $0, %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  popq %rcx
  movl %eax, -100(%rbp)
  movl $10, %eax
  pushq %rax
  movl -24(%rbp), %eax
  popq %rcx
  pushq %rax
  movl $0, %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  popq %rcx
  movl %eax, -104(%rbp)
  movl $0, %eax
  movl %eax, -4(%rbp)
  movl $0, %eax
  movl %eax, -4(%rbp)
  movl %eax, -4(%rbp)
  movl %eax, -8(%rbp)
  movl %eax, -12(%rbp)
  movl %eax, -16(%rbp)
  movl $0, %eax
  movq %rbp, %rsp
  popq %rbp
  ret
.globl add
add:
  pushq %rbp
  movq %rsp, %rbp
  movl -24(%rbp), %eax
  pushq %rax
  movl -20(%rbp), %eax
  popq %rcx
  addl %ecx, %eax
  movq %rbp, %rsp
  popq %rbp
  ret
.globl print_message
print_message:
  pushq %rbp
  movq %rsp, %rbp
  movq %rbp, %rsp
  popq %rbp
  ret
