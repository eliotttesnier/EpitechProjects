;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; syscall
;;

bits 64
global syscall
section .text

syscall:
    enter 0, 0 ; Prologue

    mov rax, rdi ; rdi -> syscall number
    mov rdi, rsi ; rsi -> arg1
    mov rsi, rdx ; rdx -> arg2
    mov rdx, rcx ; rcx -> arg3
    mov r10, r8 ; r8 -> arg4
    mov r8, r9 ; r9 -> arg5
    mov r9, [rbp+16] ; [rbp+16] -> arg6 (from stack)
    syscall

    leave ; Epilogue
    ret ; return
