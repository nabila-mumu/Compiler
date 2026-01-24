.MODEL SMALL

.STACK 1000H

.DATA

NUMBER DB '00000$'
y DW 0
z DW 0
x DW 0

.CODE

foo PROC
    PUSH BP
    SUB SP, 2
    MOV AX, 5
    MOV x, AX
    MOV AX, 6
    MOV y, AX
L0:
    MOV AX, x
    MOV BX, AX
    MOV AX, y
    XCHG AX, BX
    ADD AX, BX
    PUSH AX
    POP AX
    MOV [BP-2], AX
    MOV AX, [BP-2]
    INC AX
    MOV [BP-2], AX
    MOV AX, [BP-2]
    ADD SP, 2
    POP BP
    RET 0
foo ENDP

main PROC
    MOV AX, @DATA
    MOV DS, AX
    MOV AX, 9
    MOV z, AX
    CALL foo
    MOV AX, AX
    MOV y, AX
L1:
    MOV AX, z
    MOV BX, AX
    MOV AX, y
    XCHG AX, BX
    ADD AX, BX
    PUSH AX
    MOV AX, AX
    MOV z, AX
L2:
    MOV AX, z
    CALL print_output
    CALL new_line
    ADD SP, 0
    MOV AX, 4CH
    INT 21H
main ENDP

new_line proc
    push ax
    push dx
    mov ah,2
    mov dl,0Dh
    int 21h
    mov ah,2
    mov dl,0Ah
    int 21h
    pop dx
    pop ax
    ret
    new_line endp

print_output proc  ;print what is in ax
    push ax
    push bx
    push cx
    push dx
    push si
    lea si,number
    mov bx,10
    add si,4
    cmp ax,0
    jnge negate
    print:
    xor dx,dx
    div bx
    mov [si],dl
    add [si],'0'
    dec si
    cmp ax,0
    jne print
    inc si
    lea dx,si
    mov ah,9
    int 21h
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
    negate:
    push ax
    mov ah,2
    mov dl,'-'
    int 21h
    pop ax
    neg ax
    jmp print
    print_output endp

END MAIN
