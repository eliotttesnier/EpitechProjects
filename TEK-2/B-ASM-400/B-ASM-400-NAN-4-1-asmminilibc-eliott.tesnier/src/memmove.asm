;;
;; EPITECH PROJECT, 2025
;; ASM
;; File description:
;; memmove
;;

bits 64
global memmove
extern memcpy
section .text

memmove:
    enter 0, 0 ; Prologue

    mov rax, rdi ; Save return value

    ; Error case
    test rdi, rdi ; rdi -> dest
    jz .return

    test rsi, rsi ; rsi -> src
    jz .return

    test rdx, rdx ; rdx -> n
    jz .return

    cmp rdi, rsi
    ja .backwards ; If dest > src, copy backwards

    ; Forward copy (no overlap)
    mov rdx, rdx ; rdx -> n
    call memcpy wrt ..plt ; memcpy(rdi, rsi, rdx)
    jmp .return

.backwards:
    ; Check overlap
    mov rcx, rdx ; rcx -> counter
    add rsi, rcx ; Save rsi

    cmp rdi, rsi ; Check if dest < src + n
    jae .forward ; If no overlap, forward copy

    ; Backward copy (overlap)
    sub rsi, rcx ; Restore rsi
    lea rsi, [rsi + rcx - 1] ; rsi -> src + n - 1 (lea = Load Effective Address)
    lea rdi, [rdi + rcx - 1] ; rdi -> dest + n - 1 (lea = Load Effective Address)

.backwards_loop:
    mov r8b, byte [rsi] ; r8b -> src[last byte]
    mov byte [rdi], r8b ; dest[last byte] = src[last byte]

    dec rsi ; src[last byte]--
    dec rdi ; dest[last byte]--
    dec rcx ; counter--

    jnz .backwards_loop ; if counter != 0, loop
    jmp .return

.forward:
    sub rsi, rcx ; Restore rsi
    mov rdx, rcx ; Move count to rdx for memcpy
    call memcpy wrt ..plt ; memcpy(rdi, rsi, rdx)

.return:
    leave ; Epilogue
    ret ; return rax
