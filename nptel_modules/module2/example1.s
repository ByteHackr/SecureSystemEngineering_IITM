	.file	"example1.c"
	.text
.globl function
	.type	function, @function

 function:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	leave
	ret

	.size	function, .-function
.globl main
	.type	main, @function

 main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	$3, 8(%esp)
	movl	$2, 4(%esp)
	movl	$1, (%esp)
	call	function
	leave
	ret


	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
