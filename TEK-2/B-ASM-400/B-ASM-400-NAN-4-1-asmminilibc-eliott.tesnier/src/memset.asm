;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; memset
;;

bits 64
global memset
section .text

memset:
    enter 0, 0 ; Prologue

    push rdi ; Save rdi

    ; Error case
    test rdx, rdx ; rdx -> count
    jz .return

    test rdi, rdi ; rdi -> dest
    jz .return

    mov al, sil   ; sil -> c (sil = lower 8 bits of rsi) (al = lower 8 bits of rax)
    mov rcx, rdx ; rdx -> count

.loop:
    cmp rcx, 0 ; if count == 0
    je .return

    mov byte [rdi], al ; dest[i] = c
    inc rdi
    dec rcx

    jmp .loop

.return:
    pop rax ; Restore rdi
    leave ; Epilogue
    ret ; return
