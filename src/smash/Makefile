FLAGS = -m32 -fno-stack-protector -z execstack

EXES = example1 example3 shellcode_asm  \
	overflow1

all: $(EXES) 


$(EXES):
	gcc $(FLAGS) $@.c -o $@

clean:
	rm -f $(EXES)
