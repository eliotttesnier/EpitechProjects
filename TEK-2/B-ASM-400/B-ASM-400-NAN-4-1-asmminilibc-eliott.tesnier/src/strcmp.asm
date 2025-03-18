;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; strcmp
;;

bits 64
global strcmp
section .text

strcmp:
    enter 0, 0 ; Prologue

    xor rcx, rcx ; rcx -> i
    xor eax, eax ; eax -> return value

    ; Error case
    test rdi, rdi ; rdi -> str1
    jz .return

    test rsi, rsi ; rsi -> str2
    jz .return

.loop:
    mov al, byte [rdi + rcx] ; al -> str1[i] (al = lower 8 bits of rax)
    mov dl, byte [rsi + rcx] ; dl -> str2[i] (dl = lower 8 bits of rdx)

    test al, al ; if str1[i] == 0
    je .check_end

    cmp al, dl ; if str1[i] != str2[i]
    jne .different

    inc rcx
    jmp .loop

.check_end:
    test dl, dl ; if str2[i] == 0
    jz .equal

    mov al, 0 ; al = 0
    mov dl, byte [rsi + rcx] ; dl -> str2[i]
    jmp .different

.different:
    movzx eax, al ; eax = al (movzx = Move with Zero-Extend -> Set upper 32 bits to 0, ensrure correct comparison)
    movzx edx, dl ; edx = dl (movzx = Move with Zero-Extend)
    sub eax, edx ; eax = al - dl
    jmp .return

.equal:
    xor eax, eax ; eax = 0

.return:
    leave ; Epilogue
    ret ; return eax
