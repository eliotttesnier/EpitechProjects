;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strstr
;;

bits 64
global strstr
extern strlen
extern strncmp
section .text

strstr:
    enter 0, 0 ; Prologue

    push rdi ; Save haystack
    push rsi ; Save needle

    ; Error case
    test rdi, rdi ; if haystack == 0
    jz .not_found

    test rsi, rsi ; if needle == 0
    jz .return

    ; Get the length of the needle
    mov rdi, rsi
    call strlen wrt ..plt ; wrt = With Respect To
    test rax, rax ; if strlen(needle) == 0
    jz .return

    ; Restore pointers
    pop rsi ; needle
    pop rdi ; haystack
    push rdi ; Save haystack
    push rsi ; Save needle
    mov rdx, rax ; rdx -> length of needle

.loop:
    cmp byte [rdi], 0 ; if haystack[i] == 0
    je .not_found

    ; Compare the needle with the haystack
    pop rsi ; needle
    push rsi ; Save needle
    push rdi ; Save haystack
    push rdx ; Save length of needle
    call strncmp wrt ..plt ; wrt = With Respect To
    pop rdx ; length of needle
    pop rdi ; haystack

    test eax, eax ; if strncmp(haystack, needle, length) == 0
    jz .found

    pop rsi ; needle
    inc rdi ; haystack++
    push rdi ; Save haystack
    push rsi ; Save needle
    jmp .loop

.found:
    pop rsi ; needle
    mov rax, rdi ; rax -> haystack
    jmp .exit

.not_found:
    pop rsi ; needle
    pop rdi ; haystack
    xor rax, rax ; rax = 0
    jmp .exit

.return:
    pop rsi ; needle
    pop rax ; haystack

.exit:
    leave ; Epilogue
    ret ; return rax
