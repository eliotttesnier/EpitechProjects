;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strncmp
;;

bits 64
global strncmp
section .text

strncmp:
    enter 0, 0 ; Prologue

    xor rcx, rcx ; rcx -> i
    xor eax, eax ; eax -> return value

    ; Error case
    test rdi, rdi ; rdi -> str1
    jz .return

    test rsi, rsi ; rsi -> str2
    jz .return

    test rdx, rdx ; rdx -> n
    jz .return

.loop:
    cmp rcx, rdx ; if i == n
    je .equal

    mov al, byte [rdi + rcx] ; al -> str1[i] (al = lower 8 bits of rax)
    mov r8b, byte [rsi + rcx] ; r8b -> str2[i] (r8b = lower 8 bits of r8)

    test al, al ; if str1[i] == 0
    jz .check_end

    cmp al, r8b ; if str1[i] != str2[i]
    jne .different

    inc rcx
    jmp .loop

.check_end:
    test r8b, r8b ; if str2[i] == 0
    jz .equal

.different:
    ; (movzx = Move with Zero-Extend -> Set upper 32 bits to 0, ensrure correct comparison)
    movzx eax, al ; Zero extend AL to EAX (unsigned) (eax = lower 32 bits of rax)
    movzx r8d, r8b ; Zero extend R8B to R8D (unsigned) (r8d = lower 32 bits of r8)
    sub eax, r8d ; Subtract as unsigned values (return value = str1[i] - str2[i])
    jmp .return

.equal:
    xor eax, eax ; eax = 0

.return:
    leave ; Epilogue
    ret ; return eax
