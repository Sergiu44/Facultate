; Pentru aceasta cerinta, vom introduce operatii simple de lucru cu matrice. O matrice poate fi
; reprezentata in forma
; nrLinii nrColoane nrLinii*nrColoane_elemente
; Operatiile pe care le putem utiliza pe matrice sunt:
;   • add - adunam toate elementele din matrice cu valoarea operandului;
;   • sub - scadem din toate elementele din matrice valoarea operandului;
;   • mul - inmultim toate elementele din matrice cu valoarea operandului;
; 10
;   • div - impartim toate elementele din matrice la valoarea operandului;
;   • rot90d - rotim matricea la 90 de grade spre dreapta;
; Operatiile pe matrice contin doar instructiunea let si una dintre operatiile mentionate anterior.
; Nu sunt instructiuni complexe, precum cele de la cerintele anterioare!

.data
    str: .space 100

    formatPrintf: .asciz "%d "
    formatPrintfDivNeg: .asciz "-%d "

    delimitateBy: .asciz " "

    matrice: .space 404
    aux: .space 4
    operant: .space 4
    count: .space 4
    linii: .long 0
    coloane: .long 0
    total: .long 0

    terminator: .asciz "\n"


.text

.global main

main:
    pushl $str
    call gets  
    popl %ebx

    movl $matrice, %esi

    pushl $delimitateBy
    pushl $str
    call strtok
    popl %ebx
    popl %ebx

et_linii:
    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx

    pushl %eax
    call atoi
    popl %ebx

    movl %eax, linii

et_coloane:
    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx


    pushl %eax
    call atoi
    popl %ebx

    movl %eax, coloane

    mull linii
    movl %eax, total

    xorl %ecx, %ecx

et_for:

    cmp total, %ecx
    je et_next

    movl %ecx, aux

    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx

    pushl %eax
    call atoi
    popl %ebx

    movl aux, %ecx

    movl %eax, (%esi, %ecx, 4)
    incl %ecx
    jmp et_for

et_next:
    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx


et_verification:
    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx


    pushl %eax
    call atoi
    popl %ebx

    cmp $0, %eax
    je et_rotate

    movl %eax, operant
    
    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx

    jmp et_verify_operation

et_verify_operation:
    movl %eax, %edi

    pushl linii
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    pushl coloane
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    xorl %ecx, %ecx

    movb (%edi, %ecx, 1), %ah

    cmp $97, %ah
    je et_add

    cmp $100, %ah
    je et_div_module

    cmp $109, %ah
    je et_mul

    cmp $115, %ah
    je et_sub

et_add:
    movl (%esi, %ecx, 4), %eax

    movl %ecx, aux
    cmp $0, %eax
    je et_exit

    addl operant, %eax

    pushl %eax
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    movl aux, %ecx
    incl %ecx

    jmp et_add


et_sub:
    movl (%esi, %ecx, 4), %eax

    movl %ecx, aux
    cmp $0, %eax
    je et_exit

    subl operant, %eax

    pushl %eax
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    movl aux, %ecx
    incl %ecx

    jmp et_sub


et_mul:
    movl (%esi, %ecx, 4), %eax

    movl %ecx, aux
    cmp $0, %eax
    je et_exit

    mull operant

    pushl %eax
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    movl aux, %ecx
    incl %ecx

    jmp et_mul


et_div_module:
    xorl %ebx, %ebx
    cmp operant, %ebx
    jg et_convert

    jmp et_div

et_convert:
    subl operant, %ebx
    movl %ebx, operant

et_div:
    movl (%esi, %ecx, 4), %eax

    movl %ecx, aux
    cmp $0, %eax
    je et_exit

    xorl %edx, %edx
    movl operant, %ebx

    cmp $0, %eax
    jl et_convert_number

    divl %ebx

    jmp et_afis_neg

et_convert_number:
    subl %eax, %edx
    movl %edx, %eax

    xorl %edx, %edx
    divl %ebx
    jmp et_afis_poz


et_afis_poz:
    pushl %eax
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    movl aux, %ecx
    incl %ecx

    jmp et_div

et_afis_neg:
    pushl %eax
    pushl $formatPrintfDivNeg
    call printf
    popl %ebx
    popl %ebx

    movl aux, %ecx
    incl %ecx

    jmp et_div

et_rotate:
    pushl coloane
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    pushl linii
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx 

    xorl %edx, %edx


et_for_coloane:
    cmp coloane, %edx
    je et_exit
    
    movl linii, %ebx
    subl $1, %ebx
    movl coloane, %eax
    movl %edx, count
    mull %ebx
    movl count, %edx
    addl %edx, %eax
    movl %eax, %ecx

et_for_linii:
    movl (%esi, %ecx, 4), %eax
    cmp $0, %ecx
    jl et_increment

    movl %ecx, aux
    movl %edx, count

    pushl %eax
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx

    movl aux, %ecx
    movl count, %edx

    subl coloane, %ecx
    jmp et_for_linii


et_increment:
    incl %edx
    jmp et_for_coloane


et_exit:

    pushl $terminator
    call printf
    popl %ebx

    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80

    