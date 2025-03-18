;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strpbrk
;;

bits 64
global strpbrk
extern strchr
section .text

strpbrk:
    enter 0, 0 ; Prologue

    ; Error case
    test rdi, rdi ; if str == 0
    jz .not_found

    test rsi, rsi ; if accept == 0
    jz .not_found

.loop:
    movzx rcx, byte [rdi] ; rcx -> str[i] (movzx = Move with Zero-Extend -> Set upper 32 bits to 0, ensrure correct comparison)
    test rcx, rcx ; if str[i] == 0
    jz .not_found

    push rdi ; Save str
    push rsi ; Save accept

    ; Call strchr
    mov rdi, rsi ; 1st argument = accept
    mov rsi, rcx ; rcx -> c

    call strchr wrt ..plt ; wrt = With Respect To

    test rax, rax ; if strchr(accept, str[i]) == 0
    jnz .found

    pop rsi ; accept
    pop rdi ; str
    inc rdi ; str++
    jmp .loop

.found:
    pop rsi ; accept
    pop rdi ; str
    mov rax, rdi ; rax -> &str[i]
    jmp .return

.not_found:
    xor rax, rax ; rax = 0

.return:
    leave ; Epilogue
    ret ; return rax
