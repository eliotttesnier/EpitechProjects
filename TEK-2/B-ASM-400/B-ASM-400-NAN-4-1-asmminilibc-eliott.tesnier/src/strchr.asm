;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strchr
;;

bits 64
global strchr, index
section .text

strchr:
index:
    enter 0, 0 ; Prologue

    mov rax, rdi ; rdi -> str
    mov dl, sil ; sil -> c

    ; Error case
    test rax, rax
    jz .not_found

.loop:
    mov cl, [rax] ; current char (cl = lower 8 bits of rax)
    cmp cl, dl ; if current char == c (dl = lower 8 bits of rdx)
    je .found

    test cl, cl ; if current char == 0
    jz .check_null

    inc rax
    jmp .loop

.check_null:
    cmp dl, 0 ; if searching for null
    je .found

.not_found:
    xor rax, rax ; return value = 0

.found:
    leave ; Epilogue
    ret ; return rax
