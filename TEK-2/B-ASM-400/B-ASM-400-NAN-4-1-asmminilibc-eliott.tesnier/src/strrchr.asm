;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strrchr
;;

bits 64
global strrchr, rindex
extern strlen
section .text

strrchr:
rindex:
    enter 0, 0 ; Prologue
    sub rsp, 16 ; rbp, rsp (Align stack to 16 bytes boundary)

    ; Error case
    test rdi, rdi ; rdi -> str
    jz .not_found

    mov rdx, rsi ; rsi -> c

    call strlen wrt ..plt ; wrt = With Respect To
    mov rcx, rax ; rax -> strlen(str)

.loop:
    cmp byte [rdi + rcx], sil ; if str[i] == c
    je .found

    dec rcx
    jns .loop ; jns = Jump if Not Signed

.not_found:
    xor rax, rax ; rax = 0
    jmp .return

.found:
    lea rax, [rdi + rcx] ; rax = &str[i]

.return:
    leave ; Epilogue
    ret ; return rax
