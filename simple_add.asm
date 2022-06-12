addi $a0 $zero 40
addi $a1 $zero 12
jal mult
nop
mult: add $v0 $zero $zero
loop: andi $t1 $a0 1
blez $t1 skipadd
bgtz $t1 skipadd
add $v0 $v0 $a1
skipadd: srl $a0 $a0 1
sll $a1 $a1 1
bne $a0 $zero loop
jr $ra
