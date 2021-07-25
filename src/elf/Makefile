FLAGS = -m32 -fno-stack-protector -z execstack

EXES = hello fact

all: $(EXES) 


$(EXES):
	gcc $(FLAGS) $@.c -c 
	gcc $(FLAGS) $@.c -o $@
	gcc $(FLAGS) -S $@.c -o $@.s
	objdump --disassemble-all $@ > $@.lst


clean:
	rm -f $(EXES) $(DISS)
	rm -f *.o *.lst *.s
