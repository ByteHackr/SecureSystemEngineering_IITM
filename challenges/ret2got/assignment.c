#include <stdio.h>
#include <string.h>

#include <mylib.h>

char buf1[16];
char payload[256] = 
"\xeb\x18\x5e\x31\xc0\x89\x76\x08\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\xe8\xe3\xff\xff\xff/bin/ls         ";


void main(int argc, char **argv)
{
	node_t *n1, *n2, *n3, *n4;

	init(&headnode);
	

	n1 = newnode();
	n2 = newnode();
	n3 = newnode();

	printf("Enter n1 data\n");
	gets(n1->data);
	printf("Enter n2 data\n");
	gets(n2->data);
	printf("Enter n3 data\n");
	gets(n3->data);


	printf("Deleting node n2\n");
	delete(n2);

	printf("The list has the following elements...\n");
	print();
}

