------------------------------------------------------------------------------
                        Secure Systems Engineering
              RISE Lab, Indian Institute of Technology Madras
------------------------------------------------------------------------------
-- Smashing the stack ---

This is the readme for understanding techniques to corrupt stack, while
executing C programs. We start with basic understanding of stack layout. We
will show how to modify return address to alter program's execution flow. 
Later, we will see how an attacker could run a shell program by altering the
execution flow.

This directory contains codes from the paper
'Smashing the Stack for Fun and Profit', by Aleph One

Note that all compilations should have the option -fno-stack-protector 
to prevent any canaries added to each function.

This code should run on an Ubuntu Linux processor. To make the executables,
run

$ make

------------------------------------------------------------------------------

Stack Structure (example1.c)
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Refer to example1.c, which comprises of the main function invoking 
a function called `function' having three parameters a, b, and c.

The important parts of the assembly code for this example is present
in example1_annotated.s 

-----------------------------------------------------------------------------

Overwriting return address (example3.c)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This program shows how the return address is modified to skip an instruction.
Not that in `function', buffer1 is overflowed and a location pointed to by 
(buffer1 + 24) is incremented by 8.

The location (buffer1 + 24) is present in the stack and contains the
return address. i.e., the address in main which should be executed after
`function' is executed. This address corresponds to the line x=1 in the
main function. 

Now, the statement x = 1 gets transformed to the assembly instruction
movl   $0x1,-0x4(%rbp). The machine code for this instruction is the
following 7 byte codes: (c7 45 fc 01 00 00 00).
Now, by incrementing the return address stored in (buffer1 + 24) by
8, the 7 byte codes would be skipped, the processor would execute from
the instruction following this after function completes execution. 
Thus the x=1 statement is skipped and the printf statement would execute.
The printf would print 
Value of x is 0
instead of 
Value of x is 1.
-----------------------------------------------------------------------------

Creating a Shell Code by overflowing the stack
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Now we will create a payload, which creates a bash shell. This payload
is essentially a program, which we want to inject into the stack of
another process. 

Let us start with writing a C code for the program that we want to execute.
This C code is in shellcode.c. As we can see, shellcode.c simply invokes
the execve system call, which starts a new process depending on the
file passed in name[0]. Here, the /bin/sh shell will get created.

To build our payload, we would require this code to be written in assembly
language. This is done in shellcode_asm.c. Thus, when you compile 
shellcode_asm.c, it would do exactly the same as shellcode.c.

Now open shellcode_asm.lst, this is the disassembly of shellcode_asm.c.
The disassembly of main looks something like this...
00000000 <main>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   eb 18                   jmp    1d <main+0x1d>
   5:   5e                      pop    %esi
   6:   31 c0                   xor    %eax,%eax
   8:   89 76 08                mov    %esi,0x8(%esi)
   b:   88 46 07                mov    %al,0x7(%esi)
   e:   89 46 0c                mov    %eax,0xc(%esi)
  11:   b0 0b                   mov    $0xb,%al
  13:   89 f3                   mov    %esi,%ebx
  15:   8d 4e 08                lea    0x8(%esi),%ecx
  18:   8d 56 0c                lea    0xc(%esi),%edx
  1b:   cd 80                   int    $0x80
  1d:   e8 e3 ff ff ff          call   5 <main+0x5>
  22:   5d                      pop    %ebp
  23:   c3                      ret    

Note the similarity of shellcode_asm.c and its dissassembly.
They have the same instructions,
Important for us are the byte codes: 
eb 18 5e 31 c0 .... .... .... .... e8 e3 ff ff ff 5d c3.

These byte codes are what are used by the processor at
execution time. The processor would read the byte codes and then
intepret the instructions and execute accordingly.
We will use this byte code string eb 18 5e .... ff ff ff 5d c3
to create our payload.

Next step is to inject the payload bytecode in an executable.
Refer to overflow.c. The byte code for explaination purposes
is present in the array shellcode. In malware, the attacker would
need to find some mechanisms to inject this byte code into
a process at runtime.
The program has a large_string of 128 bytes, copied into
a local buffer, which is of 48 bytes, using the strcpy
function. This is a potential spot for a buffer overflow
exploit to take place!!!

Lets see how this can be done...
* First, we copy the address of buffer into large_string.
  Now the entire large_string contains the address of buffer.
* Next, we copy the shellcode into large string. Thus, the
  initial part of buffer contains the shellcode, while the
  remaining part comprises of the buffer address.
* Third, we invoke strcpy. Since buffer is much smaller than 
  large_string, there is a buffer overflow. Since buffer is
  present on the stack, the stack gets corrupted. The return
  address present on the stack, gets overwritten by the contents
  of large string. In most cases, the return address is going
  to be overwritten with the address of buffer.
* When strcpy completes its execution, the return address 
  gets over written with the buffer address. At the
  buffer address we have the shellcode. Thus the shellcode
  will get executed when strcpy returns creating the /bin/sh 
  shell.


