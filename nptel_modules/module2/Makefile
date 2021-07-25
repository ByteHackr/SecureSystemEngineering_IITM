FLAGS = -fno-stack-protector -z execstack -no-pie -m32

EXES = example1 example2 example3 shellcodeasm shellcodeasm_jmp \
	shellcodeasm_no0 testsc overflow1 testcode

all: $(EXES) 


$(EXES):
	gcc $(FLAGS) $@.c -o $@

clean:
	rm -f $(EXES)
