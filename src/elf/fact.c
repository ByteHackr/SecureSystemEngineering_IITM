#include <stdio.h>
#include <stdlib.h>

int calls;

void fact(int a, int *b){
	calls++;
	if (a==1) return;
	*b = *b * a;
	fact(a - 1, b);
}

int main(){
	int n, *m;

	scanf("%d", &n);
	m = malloc(sizeof(int));
	*m = 1;
	fact(n, m);
	printf("Factorial(%d) is %d\n", n, *m);
	free(m);
}



