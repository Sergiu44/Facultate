; Fie dat ca input o instructiune in limbajul de asamblare al procesorului aritmetic considerat. Se
; cere sa se afiseze la standard output evaluarea instructiunii. Pentru aceasta cerinta, spre deosebire
; de cerinta 2, se folosesc variabile introduse prin let.
; Un exemplu de input poate fi x 1 let 2 x add y 3 let x y add mul.
; Evaluarea va fi facuta astfel:
;   • se adauga x si 1 pe stiva, este gasit let, si se intelege de acum ca x = 1 in toata expresia
; aritmetica; sunt eliminati x si 1 de pe stiva;
;   • se adauga 2 si 1 pe stiva (deoarece acel x este = 1 de acum);
;   • se intalneste add, se calculeaza suma 3, se elimina 2 si 1 de pe stiva si se pastreaza doar 3;
;   • se adauga y si 3 pe stiva, este gasit let, si se intelege de acum ca y = 3 in toata expresia
; aritmetica; sunt eliminati y si 3 de pe stiva;
;   • se adauga 1 si 3 pe stiva (x, respectiv y);
;   • se efectueaza adunarea, rezultatul va fi 4, se elimina 1 si 3 de pe stiva, se adauga 4;
;   • este identificat mul, iar pe stiva aveam deja 3 (de la a treia bulinuta din explicatia curenta) si
; 4, de la bulinuta anterioara, si se calculeaza rezultatul, 12, se elimina apoi 3 si 4 de pe stiva si
; se adauga 12;
;   • nu mai sunt elemente in sir, deci rezultatul final este 12.
; Exact ca la cerinta a doua, se garanteaza ca toate operatiile vor fi aplicate pe unsigned.

.data
    str: .space 100
    
    formatScanf: .asciz "%s"
    formatPrintf: .asciz "%d\n"
    
    delimitateBy: .asciz " "
    rezultat: .space 4
    aux: .space 1

    vector_char: .space 120


.text

.global main

main:

    pushl $str
    call gets 
    popl %ebx

    movl $vector_char, %esi

    pushl $delimitateBy
    pushl $str
    call strtok
    popl %ebx
    popl %ebx

    jmp et_salut
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

    pushl %edi
    call strlen
    popl %ebx

    cmp $3, %eax
    je et_operator

    jmp et_other

et_operator:

    xorl %ecx, %ecx
    movb (%edi, %ecx, 1), %al

    cmp $97, %al
    je et_add

    cmp $100, %al
    je et_div

    cmp $108, %al
    je et_let

    cmp $109, %al
    je et_mul

    cmp $115, %al
    je et_sub

et_other:
    xorl %ecx, %ecx
    movb (%edi, %ecx, 1), %bl
    cmp $97, %bl
    jge et_variable

    movl %edi, %eax
    pushl %eax
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

et_let:

    movb aux, %ch
    movzx %ch, %ecx

    popl %ebx
    popl %eax

    movl %ebx, (%esi, %ecx, 4) 
    movl (%esi, %ecx, 4), %ebx
    jmp et_for


et_variable:
    subb $97, %bl
    movb %bl, aux
    movzx %bl, %ebx
    movl %ebx, %ecx

    movl (%esi, %ecx, 4), %ebx

    pushl %ebx
    
    jmp et_for