;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; ffs
;;

bits 64
global ffs
section .text

ffs:
    enter 0, 0

    test rdi, rdi ; Check if input is 0
    jz .return_zero

    bsf rax, rdi ; Bit Scan Forward: finds first set bit
    inc rax ; Add 1 because ffs uses 1-based indexing
    jmp .end

.return_zero:
    xor rax, rax ; Return 0 for input 0

.end:
    leave
    ret
