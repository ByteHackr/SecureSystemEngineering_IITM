 /* Buffer overflows can change execution paths */

 #include <stdio.h>

 void function(int a, int b, int c)
 {
	int * ret = NULL;
	char buffer1[16];
 
	ret = (int *)(buffer1 + 24);
	(*ret) += 8;
 }

 void main()
 {
	int x;
	x = 0;
	function(1,2,3);
	x = 1;
	printf("Value of x is %d\n", x);
 }


