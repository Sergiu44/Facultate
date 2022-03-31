; Se citesc de la tastatura n, m si 3 · n elemente care pot fi sau 0, sau cuprinse intre 1 si n, unde se
; respecta conditia 1 ≤ n, m ≤ 30. Se va genera cea mai mica permutare in sens lexicografic a
; multimii {1, ..., n}, unde fiecare element apare de exact 3 ori, avand o distanta de minimum m
; elemente intre oricare doua elemente egale, plecand de la anumite puncte fixe deja specificate.
; De exemplu, pentru n = 5, m = 1 si secventa de 15 elemente
; 1 0 0 0 0 0 3 0 0 0 0 0 0 4 5
; avem ca fiecare element din multimea {1, 2, 3, 4, 5} apare de 3 ori, si vrem sa fie cel putin m =
; 1 element distanta intre oricare doua elemente egale. Atunci, cea mai mica permutare in sens
; lexicografic, pastrand punctele fixe, este urmatoarea:
; 1 2 1 2 1 2 3 4 3 5 3 4 5 4 5
; Se vor afisa la standard output, dupa caz,
;   • sau permutarea, daca exista, in formatul de mai sus: elementele se vor afisa cu spatii intre ele
; pe ecran, iar la final recomandam sa afisati un caracter backslash n, in locul utilizarii fflush;
;   • sau −1, in cazul in care nu exista o permutare care sa satisfaca toate conditiile.

.data
    len: .space 4
    n: .space 4
    m: .space 4
    v: .space 512
    aux: .space 4
    a: .space 4
    cnt: .space 4


    neg: .long -1
    trei: .long 3
    ok: .long 0
    format_two: .asciz "%d %d"
    input: .asciz "%d"
    output: .asciz "%d "
    newLine: .asciz "\n"
    none: .asciz "-1\n"
.text
.global main
show:
    movl $1, ok
    movl $1, %ecx
show_loop:
    cmp len, %ecx
    jg show_exit

    movl $v, %edi
    cmp $0, (%edi, %ecx, 4)
    jl show_negative

    pushl %ecx
    pushl (%edi, %ecx, 4)
    pushl $output
    call printf
    popl %ebx
    popl %ebx
    popl %ecx

    show_inc: incl %ecx
    jmp show_loop
show_negative:
    movl (%edi, %ecx, 4), %eax
    xorl %edx, %edx
    mull neg
    pushl %ecx
    pushl %eax
    pushl $output
    call printf
    popl %ebx
    popl %ebx
    popl %ecx

    jmp show_inc
show_exit: 
    pushl $newLine
    call puts
    popl %ebx
    ret

valid:
    pushl %ebp
    movl %esp, %ebp

    movl $1, cnt
    movl 8(%ebp), %eax
    movl %eax, a

    decl %eax
valid_loop:
    cmp $0, %eax
    je valid_true

    movl $v, %edi
    movl 8(%ebp), %ecx

    movl (%edi, %eax, 4), %ebx # v[i]
    cmp %ebx, (%edi, %ecx, 4) #v[i], v[k]
    je cnt_inc

    pushl %eax
    movl %ebx, %eax
    xorl %edx, %edx
    mull neg
    movl %eax, %edx
    popl %eax

    cmp %edx, (%edi, %ecx, 4)
    je cnt_inc

    dec_loop: decl %eax
    jmp valid_loop

cnt_inc:
    incl cnt

    cmp $3, cnt
    jg valid_false

    movl a, %ebx
    subl %eax, %ebx

    cmp m, %ebx
    jle valid_false

    movl %eax, a
    jmp dec_loop

valid_true:
    movl $1, %edx
    jmp valid_exit

valid_false:
    movl $0, %edx
    jmp valid_exit

valid_exit:
    popl %ebp
    ret
succesor:
    pushl %ebp
    movl %esp, %ebp

    movl $v, %edi
    movl 8(%ebp), %ecx
    movl n, %ebx

    cmp %ebx, (%edi, %ecx, 4)
    jge succesor_false

    incl (%edi, %ecx, 4)
    jmp succesor_true
succesor_false:
    movl $0, %edx
    jmp succesor_exit
succesor_true:
    movl $1, %edx
    jmp succesor_exit
succesor_exit:
    popl %ebp
    ret

backt:
    pushl %ebp
    movl %esp, %ebp

    movl $v, %edi
    movl 8(%ebp), %eax

    cmp $0, (%edi, %eax, 4)
    jge backt_continuare

    movl 8(%ebp), %eax
    pushl %ecx
    pushl %ebx
    pushl %eax
    call valid
    popl %eax
    popl %ebx
    popl %ecx

    cmp $0, %edx
    je backt_exit

    movl 8(%ebp), %eax
    cmp len, %eax
    je backt_show

    movl 8(%ebp), %eax
    incl %eax
    pushl %edx
    pushl %ebx
    pushl %ecx
    pushl %eax
    call backt
    popl %eax
    popl %ecx
    popl %ebx
    popl %edx

    jmp backt_exit

backt_continuare:
    movl 8(%ebp), %eax
    movl $v, %edi
    movl $0, (%edi, %eax, 4)

    backt_while:
        movl 8(%ebp), %eax

        pushl %eax
        call succesor
        popl %eax

        cmp $0, %edx
        je backt_exit

        cmp $0, ok
        jne backt_exit

        pushl %ecx
        pushl %ebx
        pushl %eax
        call valid
        popl %eax
        popl %ebx
        popl %ecx

        cmp $0, %edx
        je backt_while

        movl 8(%ebp), %eax
        cmp %eax, len
        je backt_show_while

        movl 8(%ebp), %eax
        incl %eax
        pushl %edx
        pushl %ebx
        pushl %ecx
        pushl %eax
        call backt
        popl %eax
        popl %ecx
        popl %ebx
        popl %edx

        jmp backt_while
    jmp backt_exit

backt_show_while:
    pushl %ecx
    pushl %ebx
    pushl %eax
    pushl %edx
    call show
    popl %edx
    popl %eax
    popl %ebx
    popl %ecx
    jmp backt_while

backt_show:
    pushl %ecx
    pushl %ebx
    pushl %eax
    pushl %edx
    call show
    popl %edx
    popl %eax
    popl %ebx
    popl %ecx
    jmp backt_exit

backt_exit:
    popl %ebp
    ret

main:
    pushl $m
    pushl $n
    pushl $format_two
    call scanf
    popl %ebx
    popl %ebx
    popl %ebx

    movl n, %eax
    xorl %edx, %edx
    mull trei
    movl %eax, len

    movl $1, %ecx

loop:
    cmp len, %ecx
    jg main_continuare

    pushl %ecx
    pushl $aux
    pushl $input
    call scanf
    popl %ebx
    popl %ebx
    popl %ecx

    movl $v, %edi
    movl aux, %eax
    xorl %edx, %edx
    mull neg
    movl %eax, (%edi, %ecx, 4)

    incl %ecx
    jmp loop

main_continuare:
    pushl $1
    call backt
    popl %ebx

    cmp $0, ok
    jne et_exit

    pushl $none
    call puts
    popl %ebx

et_exit:
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80