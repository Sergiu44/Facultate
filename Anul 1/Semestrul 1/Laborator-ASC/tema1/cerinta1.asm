; Fie dat ca input un sir hexa, se cere sa se afiseze la standard output 
; instructiunea assembly de
; executat.
; De exemplu, pentru inputul A78801C00A7890EC04, se va afisa la standard output x 1 let x
; -14 div.

.data
    stringHexa: .space 500
    stringBinar: .space 500
    index: .space 4
    formatScanf: .asciz "%s"

    formatPrintf: .asciz "%s "
    formatPrintfC: .asciz "%c "
    formatPrintfNumber: .asciz "%d "
    formatPrintfNumberNegativ: .asciz "-%d "

    suma: .long 0
    sumaAux: .long 128

    strlet: .asciz "let"
    stradd: .asciz "add"
    strsub: .asciz "sub"
    strmul: .asciz "mul"
    strdiv: .asciz "div"

    terminator: .asciz "\n"

.text

.global main

main:
    pushl $stringHexa
    pushl $formatScanf
    call scanf
    popl %ebx
    popl %ebx
    
    movl $stringHexa, %edi
    movl $stringBinar, %esi
    xorl %ecx, %ecx
    xorl %ebx, %ebx

et_for:
    movb (%edi, %ecx, 1), %ah
    cmp $0, %ah
    je et_afisare

    movl %ecx, index
    jmp et_convertFirst
    
    

et_increment: 
    movl $0, %ebx
    movl %ebx, suma
    movl index, %ecx
    addl $3, %ecx
    jmp et_for


et_afisare:
    movl $4, %eax
    movl $1, %ebx
    mov $terminator, %ecx
    movl $2, %edx
    int $0x80

et_exit:
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80


et_convertFirst:

    incl %ecx
    movb (%edi, %ecx, 1), %al 

    cmp $65, %al
    je et_A_1
        
    cmp $66, %al
    je et_B_1
        
    cmp $67, %al
    je et_C_1
        
    cmp $68, %al
    je et_D_1
        
    cmp $69, %al
    je et_E_1
        
    cmp $70, %al
    je et_F_1
        
    cmp $48, %al
    je et_0_1
        
    cmp $49, %al
    je et_1_1
        
    cmp $50, %al
    je et_2_1
        
    cmp $51, %al
    je et_3_1
        
    cmp $52, %al
    je et_4_1
        
    cmp $53, %al
    je et_5_1
        
    cmp $54, %al
    je et_6_1
        
    cmp $55, %al
    je et_7_1
        
    cmp $56, %al
    je et_8_1
        
    cmp $57, %al
    je et_9_1
        

et_convertSecond:
    incl %ecx
    movb (%edi, %ecx, 1), %al 

    cmp $65, %al
    je et_A_2
        
    cmp $66, %al
    je et_B_2
        
    cmp $67, %al
    je et_C_2
        
    cmp $68, %al
    je et_D_2
        
    cmp $69, %al
    je et_E_2
        
    cmp $70, %al
    je et_F_2

    cmp $48, %al
    je et_0_2

    cmp $49, %al
    je et_1_2
        
    cmp $50, %al
    je et_2_2
        
    cmp $51, %al
    je et_3_2
        
    cmp $52, %al
    je et_4_2
        
    cmp $53, %al
    je et_5_2
        
    cmp $54, %al
    je et_6_2
        
    cmp $55, %al
    je et_7_2
       
    cmp $56, %al
    je et_8_2
        
    cmp $57, %al
    je et_9_2
        

et_decoding:
    movl %ebx, suma
    xorl %ebx, %ebx

    cmp $65, %ah
    je et_variabila
    cmp $66, %ah
    je et_variabilaAux
    cmp $67, %ah
    je et_operator

    cmp $56, %ah
    je et_number
    cmp $57, %ah
    je et_negativNumber


        et_variabila:
            pushl suma
            pushl $formatPrintfC
            call printf
            popl %ebx
            popl %ebx
            pushl $0
            call fflush
            popl %ebx
            jmp et_increment

        et_variabilaAux:
            movl sumaAux, %ebx
            addl %ebx, suma
            pushl suma
            pushl $formatPrintfC
            call printf
            popl %ebx
            popl %ebx
            pushl $0
            call fflush
            popl %ebx
            jmp et_increment

        et_operator:

            cmp $48, %al
            je afis_let

            cmp $49, %al
            je afis_add
            
            cmp $50, %al
            je afis_sub

            cmp $51, %al
            je afis_mul

            cmp $52, %al
            je afis_div


            afis_let:
                pushl $strlet
                pushl $formatPrintf
                call printf
                popl %ebx
                popl %ebx

                pushl $0
                call fflush
                popl %ebx
                jmp et_increment

            afis_add:
                pushl $stradd
                pushl $formatPrintf
                call printf
                popl %ebx
                popl %ebx
                pushl $0
                call fflush
                popl %ebx
                jmp et_increment

            afis_sub:
                pushl $strsub
                pushl $formatPrintf
                call printf
                popl %ebx
                popl %ebx
                pushl $0
                call fflush
                popl %ebx
                jmp et_increment

            afis_mul:
                pushl $strmul
                pushl $formatPrintf
                call printf
                popl %ebx
                popl %ebx
                pushl $0
                call fflush
                popl %ebx
                jmp et_increment

            afis_div:
                pushl $strdiv
                pushl $formatPrintf
                call printf
                popl %ebx
                popl %ebx
                pushl $0
                call fflush
                popl %ebx
                jmp et_increment

        et_number:
            pushl suma
            pushl $formatPrintfNumber
            call printf
            popl %ebx
            popl %ebx
            pushl $0
            call fflush
            popl %ebx
            jmp et_increment

        et_negativNumber:
            pushl suma
            pushl $formatPrintfNumberNegativ
            call printf
            popl %ebx
            popl %ebx
            pushl $0
            call fflush
            popl %ebx
            jmp et_increment

et_A_1:
    addl $160, %ebx
    jmp et_convertSecond

et_B_1:
    addl $176, %ebx
    jmp et_convertSecond

et_C_1:
    addl $192, %ebx
    jmp et_convertSecond

et_D_1:
    addl $208, %ebx
    jmp et_convertSecond

et_E_1:
    addl $224, %ebx
    jmp et_convertSecond

et_F_1:
    addl $240, %ebx
    jmp et_convertSecond

et_0_1:
    addl $0, %ebx
    jmp et_convertSecond

et_1_1:
    addl $16, %ebx
    jmp et_convertSecond

et_2_1:
    addl $32, %ebx
    jmp et_convertSecond

et_3_1:
    addl $48, %ebx
    jmp et_convertSecond

et_4_1:
    addl $64, %ebx
    jmp et_convertSecond

et_5_1:
    addl $80, %ebx
    jmp et_convertSecond

et_6_1:
    addl $96, %ebx
    jmp et_convertSecond

et_7_1:
    addl $112, %ebx
    jmp et_convertSecond

et_8_1:
    addl $128, %ebx
    jmp et_convertSecond

et_9_1:
    addl $144, %ebx
    jmp et_convertSecond




et_A_2:
    addl $10, %ebx
    jmp et_decoding

et_B_2:
    addl $11, %ebx
    jmp et_decoding

et_C_2:
    addl $12, %ebx
    jmp et_decoding

et_D_2:
    addl $13, %ebx
    jmp et_decoding

et_E_2:
    addl $14, %ebx
    jmp et_decoding

et_F_2:
    addl $15, %ebx
    jmp et_decoding

et_0_2:
    addl $0, %ebx
    jmp et_decoding

et_1_2:
    addl $1, %ebx
    jmp et_decoding

et_2_2:
    addl $2, %ebx
    jmp et_decoding

et_3_2:
    addl $3, %ebx
    jmp et_decoding

et_4_2:
    addl $4, %ebx
    jmp et_decoding

et_5_2:
    addl $5, %ebx
    jmp et_decoding

et_6_2:
    addl $6, %ebx
    jmp et_decoding

 et_7_2:
    addl $7, %ebx
    jmp et_decoding

et_8_2:
    addl $8, %ebx
    jmp et_decoding

et_9_2:
    addl $9, %ebx
    jmp et_decoding
