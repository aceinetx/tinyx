How to make a TinyX Executable
-
### 1. Assembly
Firstly we need to set up our assembly code and main function<br>
Main function does not need any labels or symbol exports, and should always be after tinyx header<br>
First thing we need to put is ```.intel_syntax noprefix```, this will reduce the use of % sign in instructions
To create a tinyx header, type 
```asm
.string "tiny"
```
This will create those bytes: 74 69 6E 79 00<br>
The header is created, now we need a main function, and to create a main function we need to set up the stack and local variables
```asm
push rbp
mov rbp, rsp

// argc
mov dword ptr [rbp-4], edi
// argv
mov qword ptr [rbp-12], rsi

// return 0;
mov eax, 0

leave
ret
```
Notice that we didn't use any labels, because they aren't neccessary to create a main function<br>
We can already compile our program!<br>
To do that, firstly we need an object file, create it by using ```as <yourcode>.asm -o <output>.o```
Now we need to link it, though tinyx executable format is technically a raw binary, we still need to link it by running ```ld --oformat binary <output>.o -o <output>```
There we have a runnable executable! to run it, do ```./tinyx <output>```
