;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strcspn
;;

bits 64
global strcspn
extern strlen
extern strpbrk
section .text

strcspn:
    enter 0, 0 ; Prologue

    push rbx ; Save rbx

    ; Error case
    test rdi, rdi ; if str == 0
    jz .return_zero

    test rsi, rsi ; if reject == 0
    jz .return_zero

    mov rbx, rdi ; rbx -> str

    ; Call strpbrk
    call strpbrk wrt ..plt ; wrt = With Respect To

    test rax, rax ; if strpbrk(str, reject) == 0
    jz .full_length

    sub rax, rbx ; rax = strpbrk(str, reject) - str
    jmp .return

.full_length:
    mov rdi, rbx ; rdi -> str
    call strlen wrt ..plt ; wrt = With Respect To
    jmp .return

.return_zero:
    xor rax, rax ; rax = 0

.return:
    pop rbx ; Restore rbx

    leave ; Epilogue
    ret ; return rax
