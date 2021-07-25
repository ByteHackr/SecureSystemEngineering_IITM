 #include <stdio.h>
 #include <stdlib.h>

 void main(){
	char *name[2];
 
	name[0] = "/bin/sh";     /* exe filename  */
	name[1] = NULL;          /* exe arguments */
	execve(name[0], name, NULL);
	exit(0);
 } 
