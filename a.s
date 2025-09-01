.data
.text
.globl main
foo:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
