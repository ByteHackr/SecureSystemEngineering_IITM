
 #include <string.h>

 void function(char *str)
 {
	char buffer[5];

	strcpy(buffer, str);
 }

 void main()
 {
	char large_string[256];
	int i;
	
	for(i=0; i<255; ++i) large_string[i] = (char) 'A';
	function(large_string);
 } 


