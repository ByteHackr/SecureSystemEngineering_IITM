	.file	"example1.c"
	.text
.globl function
	.type	function, @function
function:
	pushl	%ebp        ## Push the previous frame pointer onto stack
	movl	%esp, %ebp  ## Create the new frame pointer for this function
	subl	$16, %esp   ## allocate space for the buffers
                            ##  the minimum size allocated is multiples of 16
                            ##  therefore --> char a[5]; allocates 16 bytes
                            ##           ---> char a[9]; allocates 16 bytes
                            ##          ----> char a[17]; allocates 32 bytes
	leave
	ret
	.size	function, .-function
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	$3, 8(%esp)  ## push c onto stack
	movl	$2, 4(%esp)  ## push b onto stack
	movl	$1, (%esp)   ## push a onto stack
	call	function
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits

#### Stack has the following form
top
   c
   b
   a
   ret (address to return after function is called)
   sfp (the previous frame pointer)
   buffer1 
   buffer2
####
