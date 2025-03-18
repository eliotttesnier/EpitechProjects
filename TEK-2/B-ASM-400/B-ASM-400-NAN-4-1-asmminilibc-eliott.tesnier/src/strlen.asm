;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strlen
;;

bits 64
global strlen
section .text

strlen:
    enter 0, 0 ; Prologue

    mov rax, rdi ; rdi -> str
    xor rcx, rcx ; rcx -> i

    ; Error case
    test rdi, rdi
    jz .return

.loop:
    cmp byte [rax + rcx], 0 ; if str[i] == 0
    je .return

    inc rcx
    jmp .loop

.return:
    mov rax, rcx ; rax -> return value
    leave ; Epilogue
    ret ; return rax
