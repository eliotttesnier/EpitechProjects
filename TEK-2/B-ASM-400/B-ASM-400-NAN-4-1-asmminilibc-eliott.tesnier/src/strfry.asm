;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strfry
;;

bits 64
global strfry
extern strlen
extern rand
section .text

strfry:
    enter 0, 0 ; Prologue

    push rbx ; Save rbx
    mov rbx, rdi ; rdi -> str

    ; Call strlen
    call strlen wrt ..plt
    mov rcx, rax ; rcx -> len

    cmp rcx, 1 ; if len <= 1
    jle .end

.shuffle_loop:
    push rcx ; Save rcx
    push rdi ; Save rdi

    call rand wrt ..plt ; rand() -> rax = random number

    pop rdi ; restore rdi
    pop rcx ; restore rcx

    ; Modulo to get a random index
    xor rdx, rdx ; rdx = 0
    div rcx ; rax = rax % rcx | rdx = rax / rcx

.swap:
    ; Swap characters
    mov al, [rbx + rcx - 1] ; actual character (al = lower 8 bits of rax)
    mov r8b, [rbx + rdx] ; random character (r8b = lower 8 bits of r8)
    mov [rbx + rdx], al ; Swap characters
    mov [rbx + rcx - 1], r8b

    dec rcx
    cmp rcx, 1 ; if rcx > 1
    jg .shuffle_loop

.end:
    mov rax, rbx ; return str
    pop rbx ; Restore rbx
    leave ; Epilogue
    ret
