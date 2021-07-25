	.file	"example2.c"
	.text
.globl function
	.type	function, @function
function:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-13(%ebp), %eax
	movl	%eax, (%esp)
	call	strcpy
	leave
	ret
	.size	function, .-function
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$288, %esp
	movl	$0, 284(%esp)
	jmp	.L4
.L5:
	movl	284(%esp), %eax
	movb	$65, 28(%esp,%eax)
	addl	$1, 284(%esp)
.L4:
	cmpl	$254, 284(%esp)
	jle	.L5
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	function
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
