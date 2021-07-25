all: lib assignment

lib: 
	gcc -m32 -I. -fpic -g -c mylib.c -o mylib.o
	gcc -m32 -shared -fpic -o libmylib.so mylib.o
	objdump --disassemble-all libmylib.so > libmylib.so.diss


assignment:
	gcc -m32 -z execstack -g assignment.c -I. -L. -lmylib -o assignment
	objdump --disassemble-all assignment > assignment.diss


clean:
	rm -f *.o *.so *.*.diss *.diss
	rm -f driver assignment
