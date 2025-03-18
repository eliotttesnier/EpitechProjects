;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; memcpy
;;

bits 64
global memcpy
section .text

memcpy:
    enter 0, 0 ; Prologue

    mov rax, rdi ; rdi -> dest

    ; Error case
    test rdi, rdi ; rdi -> dest
    jz .return

    test rsi, rsi ; rsi -> src
    jz .return

    test rdx, rdx ; rdx -> n
    jz .return

    xor rcx, rcx ; rcx -> counter

.loop:
    cmp rcx, rdx ; if counter >= n, return
    jge .return

    mov r8b, [rsi + rcx] ; r8b -> src[counter]
    mov [rdi + rcx], r8b ; dest[counter] = src[counter]

    inc rcx
    jmp .loop

.return:
    leave ; Epilogue
    ret ; return rax
