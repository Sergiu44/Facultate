; Fie dat ca input o instructiune in limbajul de asamblare al procesorului aritmetic considerat, se
; cere sa se afiseze la standard output evaluarea instructiunii. Pentru aceasta cerinta, in instructiune
; nu exista variabile, ea fiind formata doar din numere intregi si operatii.
; De exemplu, poate fi data instructiunea 2 10 mul 5 div 7 6 sub add. Rezultatul trebuie sa
; fie conform urmatorului algoritm:
;   • se adauga 2 pe stiva;
;   • se adauga 10 pe stiva;
;   • se identifica operatia mul, se aplica inmultirea dintre 2 si 10, se obtine 20, se elimina 2 si 10
; de pe stiva si se pastreaza doar 20;
;   • se adauga 5 pe stiva;
;   • se identifica div - actioneaza ca 20 div 5, iar rezultatul este 4; se elimina 20 si 5 de pe stiva,
; si se pastreaza doar 4;
;   • se adauga 7 pe stiva;
;   • se adauga 6 pe stiva;
;   • se identifica sub - se calculeaza diferenta dintre 7 si 6, se obtine 1, se elimina 7 si 6 de pe stiva,
; si se adauga pe stiva valoarea 1. Atentie! in acest moment, pe stiva avem 4 (la baza) si 1 in
; varf, intrucat sub este operatie binara si a lucrat doar cu argumentele 7 si 6, dar nu si cu 4
; care era deja la baza stivei.
;   • se identifica add - se calculeaza suma dintre 1 si 4, se obtine 5, se elimina 1 si 4 de pe stiva, se
; adauga 5;
;   • am terminat de parcurs sirul, iar rezultatul obtinut este, acum, situat in varful stivei. Rezultatul acestui calcul este 5.
; 9
; 
; O sugestie de implementare a algoritmului gasiti la finalul acestui document. Important! Se
; cere evaluarea doar pe unsigned! Se garanteaza ca toate operatiile vor fi pe unsigned.

.data
    str: .space 100
    
    formatScanf: .asciz "%s"
    formatPrintf: .asciz "%d\n"
    
    delimitateBy: .asciz " "
    rezultat: .space 4

    a: .asciz "add"
    s: .asciz "sub"
    m: .asciz "mul"
    d: .asciz "div"

    aux: .space 4

.text

.global main

main:

    pushl $str
    call gets 
    popl %ebx

    pushl $delimitateBy
    pushl $str
    call strtok
    popl %ebx
    popl %ebx

    pushl %eax
    call atoi
    popl %ebx

    pushl %eax     

et_for:

    pushl $delimitateBy
    pushl $0
    call strtok
    popl %ebx
    popl %ebx

et_salut:

    cmp $0, %eax
    je et_exit


et_verification:

    movl %eax, %edi
    xorl %ecx, %ecx
    movb (%edi, %ecx, 1), %al


    cmp $97, %al
    je et_add

    cmp $100, %al
    je et_div

    cmp $109, %al
    je et_mul

    cmp $115, %al
    je et_sub

    pushl %edx
    call atoi
    popl %ebx
    pushl %eax

    jmp et_for


et_exit:

    popl %edx

    pushl %edx
    pushl $formatPrintf
    call printf 
    popl %ebx
    popl %ebx

    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80


et_add:
    popl %ebx
    popl %eax
    addl %ebx, %eax
    pushl %eax
    jmp et_for

et_sub:
    popl %ebx
    popl %eax
    subl %ebx, %eax
    pushl %eax
    jmp et_for

et_mul:
    popl %ebx
    popl %eax
    mull %ebx
    pushl %eax
    jmp et_for

et_div:
    popl %ebx
    popl %eax
    xorl %edx, %edx
    divl %ebx
    pushl %eax
    jmp et_for