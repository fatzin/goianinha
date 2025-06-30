# Código MIPS gerado pelo compilador Goianinha
# Compatível com SPIM

.data
newline: .asciiz "\n"
resultado: .word 0         # variável resultado
y: .word 0         # variável y
x: .word 0         # variável x

.text
.globl main

main:
# Início do programa principal
li $sp, 0x7fffeffc    # inicializa stack pointer
# Leitura da variável x
li $v0, 5           # syscall para read integer
syscall
sw $v0, x          # armazena valor lido na variável
# Leitura da variável y
li $v0, 5           # syscall para read integer
syscall
sw $v0, y          # armazena valor lido na variável
# Carrega variável x
lw $t0, x          # carrega valor da variável
addi $sp, $sp, -4   # aloca espaço na pilha
sw $t0, 0($sp)      # salva operando esquerdo na pilha
# Carrega variável y
lw $t0, y          # carrega valor da variável
move $t1, $t0       # move operando direito para $t1
lw $t0, 0($sp)      # recupera operando esquerdo da pilha
addi $sp, $sp, 4    # libera espaço da pilha
add $t0, $t0, $t1   # soma
sw $t0, resultado          # armazena valor na variável resultado
# Carrega variável resultado
lw $t0, resultado          # carrega valor da variável
# Escrita de valor
li $v0, 1           # syscall para print integer
move $a0, $t0       # move valor para $a0
syscall
# Nova linha
li $v0, 4           # syscall para print string
la $a0, newline     # carrega endereço da nova linha
syscall

# Finalização do programa
li $v0, 10          # syscall para exit
syscall
