;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; memfrob
;;

bits 64
global memfrob
section .text

memfrob:
    enter 0, 0 ; Prologue

    ; Error case
    test rdi, rdi ; if str == 0
    jz .return_null

    mov rax, rdi ; rdi -> str
    mov rcx, rsi ; rsi -> len

    xor rdx, rdx ; i = 0

.loop:
    cmp rdx, rcx ; if i >= len
    jge .end

    xor byte [rax + rdx], 42 ; XOR current byte with 42 (0x2A)
    inc rdx ; i++
    jmp .loop

.return_null:
    xor rax, rax ; Set return value to NULL (0)
    jmp .end

.end:
    leave ; Epilogue
    ret ; return
