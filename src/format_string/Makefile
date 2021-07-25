FLAGS = -w -m32 -g

EXES = print2a print2 print3a print3b 

all: $(EXES) 


$(EXES):
	gcc $(FLAGS) $@.c -o $@

clean:
	rm -f $(EXES)
