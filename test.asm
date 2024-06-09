.intel_syntax noprefix
.string "tiny"

push rbp
mov rbp, rsp

// argc
mov dword ptr [rbp-4], edi
// argv
mov qword ptr [rbp-12], rsi
// text
mov dword ptr [rbp-16], 670006

mov rax, 1
mov rdi, 1
lea rsi, word ptr [rbp-16]
mov rdx, 3
syscall

mov eax, 0

leave
ret